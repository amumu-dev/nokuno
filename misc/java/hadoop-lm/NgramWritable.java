import java.io.*;
import java.util.*;

import org.apache.hadoop.io.*;
import org.apache.hadoop.util.*;

/**
NgramWritable: ArrayWritable of N-gram ID
 */
public class NgramWritable extends ArrayWritable implements WritableComparable<NgramWritable> { 
    // Constructor
    public NgramWritable() {
        super(VIntWritable.class);
    }
    public NgramWritable(VIntWritable[] values) {
        super(VIntWritable.class, values);
    }
    // Comparable method
    public int compareTo(NgramWritable ngram) {
        int cmp;
        Writable[] array1 = this.get();
        Writable[] array2 = ngram.get();
        if (array1.length != array2.length) {
            return array1.length - array2.length;
        }
        for (int i = 0; i < array1.length; i++) {
            if (array1[i] instanceof VIntWritable != true) {
                return 1;
            }
            if (array2[i] instanceof VIntWritable != true) {
                return -1;
            }
            VIntWritable w1 = (VIntWritable)array1[i];
            VIntWritable w2 = (VIntWritable)array2[i];
            if ((cmp = w1.compareTo(w2)) != 0)
                return cmp;
        }
        return 0;
    }
    // Object method
    public boolean equals(Object o) {
        if (o instanceof NgramWritable == false) {
            return false;
        }
        NgramWritable ngram = (NgramWritable) o;
        Writable[] array1 = this.get();
        Writable[] array2 = ngram.get();
        if (array1.length != array2.length) {
            return false;
        }
        for (int i = 0; i < array1.length; i++) {
            Writable w1 = array1[i];
            Writable w2 = array2[i];
            if (w1.equals(w2) == false)
                return false;
        }
        return true;
    }
    public int hashCode() {
        Writable[] array = this.get();
        if (array != null && array.length > 0) {
            return array[0].hashCode();
        }
        return 0;
    }
    public String toString() {
        String result = "";
        for (Writable writable : this.get()) {
            result += writable.toString() + "\t";
        }
        return result;
    }
    // Test code
    public static byte[] serialize(Writable writable) {
        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            DataOutputStream dataOut = new DataOutputStream(out);
            writable.write(dataOut);
            dataOut.close();
            return out.toByteArray();
        } catch(IOException e) {}
        return null;
    }
    public static void deserialize(Writable writable, byte[] bytes) {
        try {
            ByteArrayInputStream in = new ByteArrayInputStream(bytes);
            DataInputStream dataIn = new DataInputStream(in);
            writable.readFields(dataIn);
            dataIn.close();
        } catch(IOException e) {}
    }
    public static void main(String[] args) {
        NgramWritable writable = new NgramWritable();
        VIntWritable[] words = new VIntWritable[3];
        words[0] = new VIntWritable(0);
        words[1] = new VIntWritable(1);
        words[2] = new VIntWritable(2);
        writable.set(words);
        byte[] bytes = serialize(writable);
        String hex = StringUtils.byteToHexString(bytes);
        System.out.println("serialize: " + hex);

        NgramWritable newWritable = new NgramWritable();
        deserialize(newWritable, bytes);
        System.out.println("deserialize: " + newWritable.toString());
    }
}
