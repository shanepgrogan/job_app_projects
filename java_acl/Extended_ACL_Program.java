import java.util.*;

public class Extended_ACL_Program{// extends Standard_ACL_Program{

    private ArrayList<Extended_ACL> aclList;
    private ArrayList<Extended_Packet> packetList;

    Extended_ACL_Program(ArrayList<Extended_ACL> acl_list, ArrayList<Extended_Packet> packet_list){
        this.aclList = acl_list;
        this.packetList = packet_list;
    }

    // Extended_ACL_Program(ArrayList<Standard_ACL> acl_list, ArrayList<Standard_Packet> packet_list){
    //     super(acl_list, packet_list);
    // }

    public ArrayList<Extended_ACL> get_acl_list(){
        return this.aclList;
    }

    public ArrayList<Extended_Packet> get_packet_list(){
        return this.packetList;
    }

    public void verifyPacket(Extended_Packet packet){

        String src = packet.getSource();
        String dest = packet.getDestination();
        int port = packet.getPortNumber();

        boolean permission, match;
        int endOfList = 0;

        for(Extended_ACL acl : this.aclList){

            permission = false;
            match = false;
            
            // this parameter is for if we reach the end of the aclList
            // with no match
            endOfList++;

            String andProduct = product(src, acl.getSourceMask());

            if(andProduct.equals(acl.getSource())){
                
                String nextAndProduct = product(dest, acl.getDestMask());
                
                if(nextAndProduct.equals(acl.getDestination())){

                    if(acl.getPortNumbers() != null){

                        if(acl.getPortNumbers().contains(port)){

                            if(acl.getPermission().equals("permit")){
                                permission = true;
                                match = true;
                            } else if(!acl.getPermission().equals("deny")){
                                System.out.println("Error: invalid permission setting");
                            } else {
                                match = true;
                            }

                        }

                    } else {

                        if(acl.getPermission().equals("permit")){
                            permission = true;
                            match = true;
                        } else if(!acl.getPermission().equals("deny")){
                            System.out.println("Error: invalid permission setting");
                        } else {
                            match = true;
                        }

                        match = true;

                    }

                }

            }

            if(match || endOfList == this.aclList.size()){
                
                System.out.print("Packet from " + packet.getSource() + " to " + packet.getDestination() + " on port " + Integer.toString(packet.getPortNumber()) + " ");
        
                if(!permission){
                    // print "denied"
                    System.out.println("denied");
                } else {
                    // print "permit"
                    System.out.println("permitted");
                }
                
                break;
           
            }

        }
  
    }

    public static String product(String addr, String mask){

        String newMask = changeMask(mask);

        /* split input strings by "." */
        String[] addrSegments = addr.split("\\.");
        String[] maskSegments = newMask.split("\\.");
        String product = "";
        String addrSegment, maskSegment;
        int addrNumber, maskNumber, andSegment;
        int len = addrSegments.length;

        /* convert packet and mask segments to bin strings */
        for(int i = 0; i < len; i++){
            addrSegment = addrSegments[i];
            maskSegment = maskSegments[i];
            addrNumber = Integer.parseInt(addrSegment);
            maskNumber = Integer.parseInt(maskSegment);
            andSegment = addrNumber & maskNumber;
            product += Integer.toString(andSegment);

            if(i < len - 1){
                product += ".";
            }
        }

        return product;

    }

    // since here 0 means check and 1 means ignore, I have this function swap the bits
    // of the input mask so that the normal bitwise operation can be performed.
    public static String changeMask(String inputMask){

        String mask = inputMask.replaceAll("0", "-0-").replace("255", "0").replace("-0-", "255");
        return mask;

    }
    
}