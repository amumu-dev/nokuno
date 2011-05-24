import java.io.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

/**
 * Reducer
 */
public class Reduce extends Reducer<Text, LongWritable, Text, LongWritable> {
    public void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {
        long sum = 0;
        for (LongWritable v : values) {
            sum += v.get();
        }
        context.write(key, new LongWritable(sum));
    }
}
