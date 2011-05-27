import java.io.*;
import java.util.*;
import java.util.Map.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.filecache.DistributedCache;

/**
 * Reducer Class
 */
public class StripesReduce extends Reducer<NgramWritable, MapWritable, NullWritable, Text> {
    private String encode;
    private int threshold;
    private HashMap<Integer, String> vocab;

    // Initialize
    protected void setup(Reducer.Context context) throws IOException, InterruptedException {
        Configuration conf = context.getConfiguration();
        threshold = Integer.parseInt(conf.get("local.threshold"));
        encode = conf.get("local.encode");
        // Hadoop version >= 0.20.2
        //Path []localFiles = context.getLocalCacheFiles();    
        Path[] localFiles = DistributedCache.getLocalCacheFiles(conf);
        if (localFiles.length == 0) return;
        String vocabulary = localFiles[0].toUri().toString();

        // Initialize vocab as reverse HashMap
        vocab = new HashMap<Integer, String>();
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(
                    new FileInputStream(vocabulary), encode));
        String line;
        int i = 0;
        while ((line = reader.readLine()) != null) {
            i++;
            vocab.put(i, line.trim());
        }
        reader.close();
    }
    // Reduce Task
    public void reduce(NgramWritable key, Iterable<MapWritable> values, Context context) throws IOException, InterruptedException {
        HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
        // Count N-gram
        for (MapWritable value : values) {
            for (Entry<Writable, Writable> entry : value.entrySet()) {
                Integer id = ((VIntWritable)entry.getKey()).get();
                if (id == 0) continue;
                Integer count1 = ((VIntWritable)entry.getValue()).get();
                Integer count2 = map.get(id);
                if (count2 == null) {
                    map.put(id, count1);
                } else {
                    map.put(id, count1 + count2);
                }
            }
        }
        // Output N-gram
        for (Entry<Integer, Integer> entry : map.entrySet()) {
            int id = entry.getKey();
            int count = entry.getValue();
            if (count >= threshold) {
                String ngramStr = ngramToString(key);
                if (ngramStr == null)
                    continue;
                String result = ngramStr + vocab.get(id) + "\t" + count;
                context.write(NullWritable.get(), new Text(result));
            }
        }
    }
    // Translate N-gram from Id to String
    public String ngramToString(NgramWritable ngram) {
        String result = "";
        for (Writable writable : ngram.get()) {
            int id = ((VIntWritable) writable).get();
            if (id == 0)
                return null;
            String word = vocab.get(id);
            result += word + "\t";
        }
        return result;
    }
}
