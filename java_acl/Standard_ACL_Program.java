import java.util.*;

public class Standard_ACL_Program{

    private ArrayList<Standard_ACL> aclList;
    private ArrayList<Standard_Packet> packetList;

    Standard_ACL_Program(ArrayList<Standard_ACL> acl_list, ArrayList<Standard_Packet> packet_list){
        this.aclList = acl_list;
        this.packetList = packet_list;
    }

    public ArrayList<Standard_ACL> get_acl_list(){
        return this.aclList;
    }

    public ArrayList<Standard_Packet> get_packet_list(){
        return this.packetList;
    }

    public void set_acl_list(ArrayList<Standard_ACL> inputList){
        this.aclList = inputList;
    }

    public void set_packet_list(ArrayList<Standard_Packet> inputList){
        this.packetList = inputList;
    }

    public void verifyPacket(Standard_Packet packet){

        String src = packet.getSource();

        boolean permission, match;
        int endOfList = 0;

        for(Standard_ACL acl : this.aclList){

            permission = false;
            match = false;
            
            // this parameter is for if we reach the end of the aclList
            // with no match
            endOfList++;

            String andProduct = product(src, acl.getSourceMask());

            if(andProduct.equals(acl.getSource())){

                if(acl.getPermission().equals("permit")){
                    permission = true;
                    match = true;
                } else if(!acl.getPermission().equals("deny")){
                    System.out.println("Error: invalid permission setting");
                } else {
                    match = true;
                }

            }

            if(match || endOfList == this.aclList.size()){
                
                System.out.print("Packet from " + packet.getSource() + " ");
        
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