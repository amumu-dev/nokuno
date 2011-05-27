import java.io.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

/**
 * Simple Combiner Class
 */
public class SimpleCombine extends Reducer<Text, LongWritable, Text, LongWritable> {
    private int cthreshold;
    protected void setup(Reducer.Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        cthreshold = Integer.parseInt(conf.get("local.cthreshold"));
    }
    public void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {
        long sum = 0;
        for (LongWritable v : values) {
            sum += v.get();
        }
        if (cthreshold == 0 || sum >= cthreshold) {
            context.write(key, new LongWritable(sum));
        }
    }
}
