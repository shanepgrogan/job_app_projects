import java.util.*;

public class TableEntry {

    // instance variables
    private int maskLength;
    private String destination, nextHop, outgoingInterface;

    // constructor
    TableEntry(int maskLength, String dest, String hop, String outgoing){

        this.maskLength = maskLength;
        this.destination = dest;
        this.nextHop = hop;
        this.outgoingInterface = outgoing;

    }

    // getters and setters
    public int getMaskLength(){
        return maskLength;
    }

    public String getMask() {
        String mask;
        if(maskLength == 32) {
            mask = "255.255.255.255";
        } else if(maskLength == 24){
            mask = "255.255.255.0";
        } else if(maskLength == 16){
            mask = "255.255.0.0";
        } else if(maskLength == 8){
            mask = "255.0.0.0";
        } else {
            mask = "0.0.0.0";
        }
        return mask;
    }

    public String getDestination() {
        return destination;
    }

    public String getNextHop() {
        return nextHop;
    }

    public String getOutgoingInterface() {
        return outgoingInterface;
    }

    public void setMask(int newMaskLength) {
        this.maskLength = newMaskLength;
    }

    public void setDestination(String newDest) {
        this.destination = newDest;
    }

    public void setNextHop(String newHop) {
        this.nextHop = newHop;
    }

    public void setOutgoingInterface(String newOutgoing) {
        this.outgoingInterface = newOutgoing;
    }

    public String toString(){
        return this.getMask() + " " + destination + " " + nextHop + " " + outgoingInterface;
    }

}
