import java.io.*;
import java.util.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.hadoop.util.*;

public class SortByFrequency {

    public static class ReverseMapper extends Mapper<LongWritable, Text, LongWritable, Text> {
        public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
            String[] splited = value.toString().split("\t", 2);
            if (splited.length != 2) return;
            context.write(new LongWritable(Long.parseLong(splited[1])), new Text(splited[0]));
        }
    }

    public static class ReverseReducer extends Reducer<LongWritable, Text, Text, LongWritable> {
        public void reduce(LongWritable key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
            for (Text val : values) {
                context.write(val, key);
            }
        }
    }
}
