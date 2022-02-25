import java.util.*;

public class RoutingTable {

    // instance variables
    private static ArrayList<TableEntry> table;

    // constructor
    RoutingTable(ArrayList<TableEntry> table){
        this.table = table;
    }

    /* returns list of unique masks in routing table entries
    * sorted by descending length (i.e. number of ones) */
    public ArrayList<String> uniqueMasks(){
        ArrayList<Integer> maskLengthList = new ArrayList<Integer>();
        ArrayList<String> maskList = new ArrayList<String>();
        int maskLength;
        String mask;
        for(TableEntry entry : table){
            maskLength = entry.getMaskLength();
            if(!maskLengthList.contains(maskLength)){
                maskLengthList.add(maskLength);
            }
        }

        Collections.sort(maskLengthList, Collections.reverseOrder());

        for(int length : maskLengthList){
            if(length == 32) {
                mask = "255.255.255.255";
            } else if(length == 24){
                mask = "255.255.255.0";
            } else if(length == 16){
                mask = "255.255.0.0";
            } else if(length == 8){
                mask = "255.0.0.0";
            } else {
                mask = "0.0.0.0";
            }
            maskList.add(mask);
        }
        return maskList;
    }

    public ArrayList<String> getMasks() {

        ArrayList<String> masks = new ArrayList<String>();
        TableEntry entry;
        int numEntries = table.size();
        for(int i = 0; i < numEntries; i++){
            entry = table.get(i);
            masks.add(entry.getMask());
        }
        return masks;

    }

    public ArrayList<TableEntry> getTable(){
        return table;
    }

    public void setTable(ArrayList<TableEntry> newTable){
        this.table = newTable;
    }

}
