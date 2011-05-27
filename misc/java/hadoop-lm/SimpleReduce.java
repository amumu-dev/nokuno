import java.io.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

/**
 * Simple Reducer Class
 */
public class SimpleReduce extends Reducer<Text, LongWritable, Text, LongWritable> {
    private int threshold;
    protected void setup(Reducer.Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        threshold = Integer.parseInt(conf.get("local.threshold"));
    }
    public void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {
        long sum = 0;
        for (LongWritable v : values) {
            sum += v.get();
        }
        if (sum >= threshold) {
            context.write(key, new LongWritable(sum));
        }
    }
}
