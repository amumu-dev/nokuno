import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.lib.input.*;
import org.apache.hadoop.mapreduce.lib.output.*;
import org.apache.hadoop.filecache.DistributedCache;

/**
 * Ngram Count with Hadoop MapReduce
 */
public class NgramCount extends Configured implements Tool {
    public void usage(){
        String usage_text =
            "USAGE: \n" +
            " hadoop jar ngram-count.jar [-files vocabulary.txt] -i INPUT_PATH -o OUTPUT_PATH [options]\n" +
            "OPTIONS:\n" +
            " -f\tformat :      text(default), sequence\n" +
            " -a\tall-gram      default: false\n" +
            " -p\tstripes       default: false\n" +
            " -n\tngram num:    default: 3\n" +
            " -r\treducer num : default: 10\n" +
            " -t\tthreshold:    default: 10\n" +
            " -c\tcombine threshold:  default: 0\n" +
            " -s\tsplit:        default: 1000000000\n" +
            " -m\tmemory:       default: 0\n" +
            " -l\tlimit:        default: 10000\n" +
            " -g\tsampling rate:    default: 1.0\n" +
            " -h\tprint help\n";
        System.err.println(usage_text);
        System.exit(1);
    }
    public int run(String[] args) throws Exception {
        // Default Settings
        String inputPath    = "";
        String outputPath   = "";
        String format       = "text";
        String encode       = "UTF-8";
        boolean allgram     = false;
        boolean stripes     = false;
        int ngramNum        = 3;
        int reduceNum       = 10;
        int threshold       = 10;
        int cthreshold       = 0;
        int split           = 1000000000;
        int memory          = 0;
        int limit           = 10000;
        double sampling      = 1.0;

        // Arguments
        for(int i=0; i<args.length; ++i){
            if("-i".equals(args[i])){
                inputPath = args[++i];
            }else if("-o".equals(args[i])){
                outputPath = args[++i];
            }else if("-f".equals(args[i])){
                format = args[++i];
            }else if("-e".equals(args[i])){
                encode = args[++i];
            }else if("-a".equals(args[i])){
                allgram = true;
            }else if("-p".equals(args[i])){
                stripes = true;
            }else if("-n".equals(args[i])){
                ngramNum = Integer.parseInt(args[++i]);
            }else if("-r".equals(args[i])){
                reduceNum = Integer.parseInt(args[++i]);
            }else if("-t".equals(args[i])){
                threshold = Integer.parseInt(args[++i]);
            }else if("-c".equals(args[i])){
                cthreshold = Integer.parseInt(args[++i]);
            }else if("-s".equals(args[i])){
                split   = Integer.parseInt(args[++i]);
            }else if("-m".equals(args[i])){
                memory  = Integer.parseInt(args[++i]);
            }else if("-l".equals(args[i])){
                limit = Integer.parseInt(args[++i]);
            }else if("-g".equals(args[i])){
                sampling = Double.parseDouble(args[++i]);
            }else if("-h".equals(args[i])){
                usage();
            }
        }
        if (inputPath.equals("") || outputPath.equals("")){
            System.err.println("input & output path must be set!");
            usage();
        }
        // Display Options
        String options = "set options are ...\n" +
            " inputPath : " + inputPath + "\n" +
            " outputPath: " + outputPath + "\n" +
            " format : "    + format + "\n" +
            " encode : "    + encode + "\n" +
            " allgram : "   + Boolean.toString(allgram) + "\n" +
            " stripes : "   + Boolean.toString(stripes) + "\n" +
            " ngramNum : "  + Integer.toString(ngramNum) + "\n" +
            " reduceNum : " + Integer.toString(reduceNum) + "\n" +
            " threshold : " + Integer.toString(threshold) + "\n" +
            " cthreshold : " + Integer.toString(cthreshold) + "\n" +
            " split : " + Integer.toString(split) + "\n" +
            " memory : " + Integer.toString(memory) + "\n" +
            " limit : " + Integer.toString(limit) + "\n" +
            " sampling : " + Double.toString(sampling) + "\n" +
            "";
        System.err.println(options);

        // Settings
        Configuration conf = getConf();
        conf.setStrings("local.format", format);
        conf.setStrings("local.encode", encode);
        conf.setStrings("local.allgram", Boolean.toString(allgram));
        conf.setStrings("local.ngramNum", Integer.toString(ngramNum));
        conf.setStrings("local.threshold", Integer.toString(threshold));
        conf.setStrings("local.cthreshold", Integer.toString(cthreshold));
        conf.setStrings("local.limit", Integer.toString(limit));
        if (cthreshold > 1 && split > 0)
            conf.setStrings("mapred.min.split.size", Integer.toString(split));
        if (memory > 0)
            conf.setStrings("mapred.child.java.opts", "-Xmx" + Integer.toString(memory) + "m");


        // Create the Job
        Job job = new Job(conf);
        job.setJarByClass(NgramCount.class);
        if (stripes) {
            job.setJobName(Integer.toString(ngramNum)+"gramCount (Stripes)");
            job.setMapperClass(StripesMap.class);
            job.setReducerClass(StripesReduce.class);
            job.setOutputKeyClass(NgramWritable.class);
            job.setOutputValueClass(MapWritable.class);
        } else {
            job.setJobName(Integer.toString(ngramNum)+"gramCount");
            job.setMapperClass(SimpleMap.class);
            job.setReducerClass(SimpleReduce.class);
            job.setCombinerClass(SimpleCombine.class); 
            job.setOutputKeyClass(Text.class);
            job.setOutputValueClass(LongWritable.class);
        }
        if (format.equals("text")) {
            job.setInputFormatClass(TextInputFormat.class);
        } else if (format.equals("sequence")) {
            job.setInputFormatClass(SequenceFileInputFormat.class);
        }
        job.setOutputFormatClass(TextOutputFormat.class);
        FileInputFormat.setInputPaths(job, inputPath);
        FileOutputFormat.setOutputPath(job, new Path(outputPath));
        if (sampling != 1.0) {
            FileInputFormat.setInputPathFilter(job, RandomSampling.class);
        }
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
