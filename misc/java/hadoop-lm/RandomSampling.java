import java.util.*;
import org.apache.hadoop.fs.*;

public class RandomSampling implements PathFilter {
    private static List<Boolean> pattern;
    private static int counter;
    public static void set(int size, double rate) {
        pattern = new ArrayList<Boolean>();
        for (int i = 0; i < size; i++) {
            if (i < size * rate)
                pattern.add(true);
            else
                pattern.add(false);
        }
        Collections.shuffle(pattern);
        counter = 0;
    }
    public boolean accept(Path path) {
        counter ++;
        if (counter > pattern.size())
            counter = 0;
        return pattern.get(counter);
    }
}
