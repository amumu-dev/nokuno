import java.io.*;
import java.util.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;

/**
 * Simple Mapper Class
 */
public class SimpleMap extends Mapper <Object, Text, Text, LongWritable> {
    private int ngramNum;
    private boolean allgram;
    private String format;

    // load settings
    protected void setup(Mapper.Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        ngramNum    = Integer.parseInt(conf.get("local.ngramNum"));
        allgram     = Boolean.parseBoolean(conf.get("local.allgram"));
        format      = conf.get("local.format");
    }
    // Map Task: Tokenize and Output
    public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
        List<String> words = tokenize(value.toString());
        if (!allgram) {
            outputNgram(words, context);
        } else {
            outputNgramAll(words, context);
        }
    }
    // Tokenize
    public List<String> tokenize(String text) {
        List<String> words = new ArrayList<String>();
        StringTokenizer tokenizer = new StringTokenizer(text);
        while (tokenizer.hasMoreTokens()) {
            words.add(tokenizer.nextToken());
        }
        return words;
    }
    // Output N-gram
    public void outputNgram(List<String> words, Context context) throws IOException, InterruptedException {
        for (int i = 0; i < words.size() - ngramNum + 1; i++) {
            String ngram = new String();
            for (int j = 0; j < ngramNum; j++) {
                ngram += words.get(i+j);
                if (j != ngramNum-1) {
                    ngram += " ";
                }
            }
            context.write(new Text(ngram), new LongWritable(1L));
        }
    }
    // Output All 1-gram to N-gram
    public void outputNgramAll(List<String> words, Context context) throws IOException, InterruptedException {
        for (int j = 0; j < words.size(); j++) {
            String ngram = new String();
            for (int i = 0; i < ngramNum; i++) {
                if (i + j < words.size()) {
                    ngram += words.get(i+j);
                    context.write(new Text(ngram), new LongWritable(1L));
                    ngram += " ";
                }
            }
        }
    }
}
