import java.io.*;
import java.util.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

/**
 * Mapper Class
 */
public class Map extends Mapper <Object, Text, Text, LongWritable> {
    private int ngramNum;

    // load settings
    protected void setup(Mapper.Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        ngramNum = Integer.parseInt(conf.get("local.ngramNum"));
    }
    // Map: Tokenize and Output
    public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
        List<String> words = new ArrayList<String>();
        StringTokenizer tokenizer = new StringTokenizer(value.toString());
        while (tokenizer.hasMoreTokens()) {
            words.add(tokenizer.nextToken());
        }
        outputNgram(words, context);
    }
    // Output N-gram
    public void outputNgram(List<String> words, Context context) throws IOException, InterruptedException {
        LongWritable one = new LongWritable(1L);
        for (int i = 0; i < words.size() - ngramNum + 1; i++) {
            String ngram = new String();
            for (int j = 0; j < ngramNum; j++) {
                ngram += words.get(i+j);
                if (j != ngramNum-1) {
                    ngram += " ";
                }
            }
            context.write(new Text(ngram), one);
        }
    }
}
