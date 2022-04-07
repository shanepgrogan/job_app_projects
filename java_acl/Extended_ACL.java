import java.util.*;

public class Extended_ACL extends Standard_ACL{

    // instance vars
    private String dest_ip;
    private String dest_mask;
    private String protocol;
    private ArrayList<Integer> port_range;

    // constructor
    Extended_ACL(int acl_num, String perm, String src_ip, String src_mask, String dest_ip, String dest_mask, String protocol, ArrayList<Integer> range){
        super(acl_num, perm, src_ip, src_mask);
        this.dest_ip = dest_ip;
        this.dest_mask = dest_mask;
        this.protocol = protocol;
        this.port_range = range;
    }

    Extended_ACL(int acl_num, String perm, String src_ip, String src_mask, String dest_ip, String dest_mask, String protocol){
        super(acl_num, perm, src_ip, src_mask);
        this.dest_ip = dest_ip;
        this.dest_mask = dest_mask;
        this.protocol = protocol;
        this.port_range = null;
    }

    // methods

    public String getDestination(){
        return this.dest_ip;
    }

    public String getDestMask(){
        return this.dest_mask;
    }

    public String getProtocol(){
        return this.protocol;
    }

    public ArrayList<Integer> getPortNumbers(){
        return this.port_range;
    }

    public void printACL(){
        System.out.print("access-list  " + this.getACLNumber() + "  " + this.getPermission() + "  " + this.protocol + "  " + this.getSource() + "  " + 
            this.getSourceMask() + "  " + this.dest_ip + "  " + this.dest_mask);
        if(this.port_range != null){
            System.out.print("  range " + Integer.toString(this.port_range.get(0)) + "-" + Integer.toString(this.port_range.get(this.port_range.size() - 1)));
        }
        System.out.print("\n");
    }

}