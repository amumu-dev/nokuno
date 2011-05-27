import java.io.*;
import java.util.*;
import java.util.Map.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.filecache.DistributedCache;

/**
 * Stripes Mapper Class
 */
public class StripesMap extends Mapper <Object, Text, NgramWritable, MapWritable> {
    private String format;
    private String encode;
    private boolean allgram;
    private int limit;
    private int ngramNum;
    private int cthreshold;
    private HashMap<NgramWritable, MapWritable> stripes;
    private HashMap<String, Integer> vocab;

    // Initialize
    protected void setup(Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        ngramNum = Integer.parseInt(conf.get("local.ngramNum"));
        allgram     = Boolean.parseBoolean(conf.get("local.allgram"));
        format = conf.get("local.format");
        encode = conf.get("local.encode");
        // Hadoop version >= 0.20.2
        //Path[] localFiles = context.getLocalCacheFiles();    
        Path[] localFiles = DistributedCache.getLocalCacheFiles(conf);
        if (localFiles.length == 0) return;
        String vocabulary = localFiles[0].toUri().toString();

        // Initialize Stripes
        stripes = new HashMap<NgramWritable, MapWritable>();

        // Initialize Vocab
        vocab = new HashMap<String, Integer>();
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(
                    new FileInputStream(vocabulary), encode));
        String line;
        int i = 0;
        while ((line = reader.readLine()) != null) {
            i++;
            vocab.put(line.trim(), i);
        }
        reader.close();
    }
    // Map Task
    public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
        List<VIntWritable> words = analyzeText(value.toString());
        if (!allgram) {
            updateStripes(words);
        } else {
            updateStripesAll(words);
        }
        if (stripes.size() > limit) {
            writeStripes(context);
            stripes.clear();
        }
    }
    // Finish
    public void cleanup(Context context) throws IOException, InterruptedException {
        writeStripes(context);
    }
    // Analyze
    private List<VIntWritable> analyzeText(String input) throws IOException, InterruptedException {
        List<VIntWritable> words = new ArrayList<VIntWritable>();
        StringTokenizer tokenizer = new StringTokenizer(input);
        while (tokenizer.hasMoreTokens()) {
            String token = tokenizer.nextToken();
            VIntWritable id =  word2id(token);
            words.add(id);
        }
        return words;
    }
    // Create N-gram and Update
    public void updateStripes(List<VIntWritable> words) {
        for (int i = 0; i < words.size() - ngramNum; i++) {
            List<VIntWritable> sublist = words.subList(i, i+ngramNum-1);
            VIntWritable[] ids = new VIntWritable[ngramNum-1];
            sublist.toArray(ids);
            VIntWritable id = words.get(i+ngramNum-1);
            if (ids == null || id == null)
                continue;

            NgramWritable key = new NgramWritable(ids);
            MapWritable value = stripes.get(key);
            if (value == null) {
                value = new MapWritable();
                value.put(id, new VIntWritable(1));
                stripes.put(key, value);
            } else {
                VIntWritable count = (VIntWritable)(value.get(id));
                if (count == null) {
                    value.put(id, new VIntWritable(1));
                } else {
                    count.set(count.get()+1);
                }
            }
        }
    }
    // Create N-gram and Update
    public void updateStripesAll(List<VIntWritable> words) {
        for (int j = 2; j <= ngramNum; j++) {
            for (int i = 0; i < words.size() - j + 1; i++) {
                List<VIntWritable> sublist = words.subList(i, i+j-1);
                VIntWritable[] ids = new VIntWritable[j-1];
                sublist.toArray(ids);
                VIntWritable id = words.get(i+j-1);
                if (ids == null || id == null)
                    continue;

                NgramWritable key = new NgramWritable(ids);
                MapWritable value = stripes.get(key);
                if (value == null) {
                    value = new MapWritable();
                    value.put(id, new VIntWritable(1));
                    stripes.put(key, value);
                } else {
                    VIntWritable count = (VIntWritable)(value.get(id));
                    if (count == null) {
                        value.put(id, new VIntWritable(1));
                    } else {
                        count.set(count.get()+1);
                    }
                }
            }
        }
    }
    // Translate Word to Id
    public VIntWritable word2id(String token) {
        Integer id = vocab.get(token);
        if (id == null) {
            return new VIntWritable(0);
        }
        return new VIntWritable(id);
    }

    // Write
    private void writeStripes(Context context) throws IOException, InterruptedException {
        for (Entry<NgramWritable, MapWritable> entry : stripes.entrySet()) {
            NgramWritable key = entry.getKey();
            MapWritable value = entry.getValue();
            context.write(key, value);
        }
    }
}
