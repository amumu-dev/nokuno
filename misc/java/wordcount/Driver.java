import java.io.*;
import java.util.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.hadoop.util.*;

public class Driver {

    public static void main(String[] args) throws Exception {

        // At first, the driver parse options and set to configure object
        Configuration conf = new Configuration();
        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
        if (otherArgs.length < 2) {
            System.err.println("Usage: wordcount <in> <out> (<num>) (<threshold>)");
            System.exit(2);
        }
        String inputPath = otherArgs[0];
        String outputPath = otherArgs[1];
        String tempPath = otherArgs[1] + "_temp";
        int numReduceTasks  = 16 * 4;
        if (otherArgs.length > 2) {
            numReduceTasks = Integer.parseInt(otherArgs[2]);
        }
        int threshold = 10;
        if (otherArgs.length > 3) {
            threshold = Integer.parseInt(otherArgs[3]);
        }
        conf.setStrings("local.threshold", Integer.toString(threshold));

        // Second, run the word count job and output (word, frequency) pair
        {
            Job job = new Job(conf, "WordCount");
            job.setJarByClass(WordCount.class);
            job.setMapperClass(WordCount.TokenizerMapper.class);
            job.setCombinerClass(WordCount.IntSumCombiner.class);
            job.setReducerClass(WordCount.IntSumReducer.class);
            job.setOutputKeyClass(Text.class);
            job.setOutputValueClass(LongWritable.class);
            job.setNumReduceTasks(numReduceTasks); 
            FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
            FileOutputFormat.setOutputPath(job, new Path(tempPath));
            Boolean result = job.waitForCompletion(true);
            if (!result)
                System.exit(1);
        }
        // Third, sort the result of word count by frequency
        {
            Job job = new Job(conf, "SortByFrequency");
            job.setJarByClass(SortByFrequency.class);
            job.setMapperClass(SortByFrequency.ReverseMapper.class);
            job.setReducerClass(SortByFrequency.ReverseReducer.class);
            job.setOutputKeyClass(LongWritable.class);
            job.setOutputValueClass(Text.class);
            job.setNumReduceTasks(1); 
            job.setSortComparatorClass(LongWritable.Comparator.class);
            FileInputFormat.addInputPath(job, new Path(tempPath + "/part*"));
            FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
            Boolean result = job.waitForCompletion(true);
            if (!result)
                System.exit(1);
        }
        // Finally, delete temporary directory for the sort
        {
            FileSystem fs = FileSystem.get(conf);
            fs.delete(new Path(tempPath), true);
        }
        System.exit(0);
    }
}
