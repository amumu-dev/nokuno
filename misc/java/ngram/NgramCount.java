import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;

/**
 * NgramCount
 */
public class NgramCount extends Configured implements Tool {
    public void usage(){
        String usage_text =
            "USAGE: \n" +
            " hadoop jar ngram.jar -i INPUT_PATH -o OUTPUT_PATH [options]\n" +
            "OPTIONS:\n" +
            " -n\tngram (default: 3)\n" +
            " -r\treducer num (default: 76)\n" +
            " -h\tprint help\n";
        System.err.println(usage_text);
        System.exit(1);
    }
    public int run(String[] args) throws Exception {
        // Default Settings
        String inputPath    = "";
        String outputPath   = "";
        int ngramNum        = 3;
        int reduceNum       = 76;

        // Arguments
        for(int i=0; i<args.length; ++i){
            if("-i".equals(args[i])){
                inputPath = args[++i];
            }else if("-o".equals(args[i])){
                outputPath = args[++i];
            }else if("-n".equals(args[i])){
                ngramNum = Integer.parseInt(args[++i]);
            }else if("-r".equals(args[i])){
                reduceNum = Integer.parseInt(args[++i]);
            }else if("-h".equals(args[i])){
                usage();
            }
        }
        if (inputPath.equals("") || outputPath.equals("")){
            System.err.println("input & output path must be set!");
            usage();
        }
        // Display Options
        String options = "set options are ...\n"+
            " inputPath : " + inputPath+"\n"+
            " outputPath: " + outputPath+"\n"+
            " ngramNum : "  + Integer.toString(ngramNum)+"\n"+
            " reduceNum : " + Integer.toString(reduceNum)+"\n";
        System.err.println(options);

        // Settings
        Configuration conf = getConf();
        conf.setStrings("local.ngramNum", Integer.toString(ngramNum));


        // Create Job
        Job job = new Job(conf);
        job.setJarByClass(NgramCount.class);
        job.setJobName("NgramCount");
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(LongWritable.class);
        job.setMapperClass(Map.class);
        job.setReducerClass(Reduce.class);
        job.setCombinerClass(Reduce.class);
        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);
        FileInputFormat.setInputPaths(job, inputPath);
        FileOutputFormat.setOutputPath(job, new Path(outputPath));
        job.setNumReduceTasks(reduceNum); 

        // Run!
        boolean result = job.waitForCompletion(true);

        return result ? 0 : 1;
    }

    public static void main(String[] args) throws Exception {
        int res = ToolRunner.run( new Configuration(), new NgramCount(), args);
        System.exit(res);
    }
}
