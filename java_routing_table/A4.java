import java.io.*;
import java.util.*;

public class A4 {

    public static void main(String[] args) throws FileNotFoundException, IOException {

        /* Initialize storage arrays and routing table */
        RoutingTable routingTable;
        ArrayList<TableEntry> table = new ArrayList<TableEntry>();
        ArrayList<String> packets = new ArrayList<String>();
        ArrayList<String> outputList = new ArrayList<String>();
        String packet;

        try{

            /* open RoutingTable.txt (or whichever input file is being used) and parse list */
            Scanner promptScanner = new Scanner(System.in);
            System.out.println("Enter routing table filename (if not the sample file 'RoutingTable.txt', add file to directory before trying to use an input):");
            String routingName = promptScanner.next();
            System.out.println("Enter filename with list of packets (if not the sample file 'RandomPackets.txt', add file to directory before trying to use an input):");
            String packetName = promptScanner.next();
            File file1 = new File(routingName);//"RoutingTable.txt");
            File file2 = new File(packetName);//"RandomPackets.txt");
            Scanner s1 = new Scanner(file1);
            Scanner s2 = new Scanner(file2);

            while(s1.hasNext()){

                String string = s1.nextLine();
                String[] split = string.split("/");
                String dest = split[0];
                int maskLength = Integer.parseInt(split[1]);
                String hop = s1.nextLine();
                String outgoing = s1.nextLine();

                TableEntry entry = new TableEntry(maskLength, dest, hop, outgoing);
                table.add(entry);

            }
            s1.close();

            /* initialize routing table with table list */
            routingTable = new RoutingTable(table);

            while(s2.hasNextLine()){
                packet = s2.next();
                packets.add(packet);
            }

            /* Route the random packets */

            ArrayList<String> masks = routingTable.uniqueMasks();
            ArrayList<String> entryMasks = routingTable.getMasks();
            String mask, andProduct, entryMask, matchMask, entryDest, matchHop, matchOutgoing, matchDest;
            int index, numMasks, numPackets;
            boolean match, entryIncrement;

            numMasks = masks.size();
            numPackets = packets.size();

            /* iterate over packets */
            for(int packetIndex = 0; packetIndex < numPackets; packetIndex++){

                packet = packets.get(packetIndex);

                /* here, iterate over masks */
                TableEntry entry;
                int maskIndex = 0;
                int entryIndex = 0;
                mask = masks.get(maskIndex);
                andProduct = product(packet,mask);
                match = false;
                matchHop = null;
                matchOutgoing = null;
                matchDest = null;
                entryIncrement = false;

                /* compare each unique mask to that of each
                * entry in the routing table. if there's a match,
                * check if the product matches the destination
                * for that entry. if there's a match, choose the
                * next hop. else, go the next entry with that mask.
                * if no other entries with that mask are in the table,
                * then choose the next unique mask and repeat.*/
                while(!match){
                    entry = table.get(entryIndex);
                    entryMask = entry.getMask();
                    entryDest = entry.getDestination();

                    /* check for match */
                    if(mask.equals(entryMask)){

                    /* checks if there is an entry with this mask
                          if there's a match, check if the AND matches the destination
                          if no match, move on to the next element and return to the top
                              of the while loop. */
                        if(andProduct.equals(entryDest)){
                            match = true;
                            matchMask = entryMask;
                            matchHop = entry.getNextHop();
                            matchOutgoing = entry.getOutgoingInterface();
                            matchDest = entryDest;
                        } else {
                            entryIndex++;
                            entryIncrement = true;
                        }
                    } else {
                        entryIndex++;
                        entryIncrement = true;
                    }

                    if(entryIncrement) {
                        if (entryIndex == table.size()) {
                            maskIndex++;
                            if(maskIndex == numMasks){
                                /* here, we've exhausted all the unique masks */
                                break;
                            } else {
                                mask = masks.get(maskIndex);
                                andProduct = product(packet, mask);
                                entryIndex = 0;
                            }
                        }
                    }
                }

                String[] splitPacket = packet.split("\\.");

                int firstSegment = Integer.parseInt(splitPacket[0]);
                if(firstSegment == 127) {
                    outputList.add(packet + " is loopback; discarded\n");
                } else if(firstSegment >= 224){
                    outputList.add(packet + " is malformed; discarded\n");
                } else if(match) {
                    if (Objects.equals(matchHop, "-")) {
                        outputList.add(packet + " will be forwarded on the directly connected network on interface " + matchOutgoing + "\n");
                    } else {
                        outputList.add(packet + " will be forwarded to " + matchHop + " out on interface " + matchOutgoing + "\n");
                    }
                }
            }

        } catch(FileNotFoundException e) {
            System.out.println("Error: File Not Found!\n");
        }

        try{
            BufferedWriter writer = new BufferedWriter(new FileWriter("RoutingOutput.txt"));
            for(String line : outputList){
                writer.write(line);
            }
            writer.close();
        } catch(IOException e){
            System.out.println("Error: IO Exception");
        }

    }

    /* performs bitwise AND on packet and mask and returns string */
    public static String product(String packet, String mask){

        /* split input strings by "." */
        String[] packetSegments = packet.split("\\.");
        String[] maskSegments = mask.split("\\.");
        String product = "";
        String packetSegment, maskSegment;
        int packetNumber, maskNumber, andSegment;
        int len = packetSegments.length;

        /* convert packet and mask segments to bin strings */
        for(int i = 0; i < len; i++){
            packetSegment = packetSegments[i];
            maskSegment = maskSegments[i];
            packetNumber = Integer.parseInt(packetSegment);
            maskNumber = Integer.parseInt(maskSegment);
            andSegment = packetNumber & maskNumber;
            product += Integer.toString(andSegment);

            if(i < len - 1){
                product += ".";
            }
        }

        return product;

    }

}
