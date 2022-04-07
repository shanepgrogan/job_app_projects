import java.util.*;

public class Standard_ACL{
    
    // instance vars
    private int acl_num;
    private String permission;
    private String src_ip;
    private String src_mask;

    // constructor
    Standard_ACL(int acl_num, String perm, String ip, String mask){
        this.acl_num = acl_num;
        this.permission = perm;
        this.src_ip = ip;
        this.src_mask = mask;
    }

    // methods

    public int getACLNumber(){
        return this.acl_num;
    }

    public String getPermission(){
        return this.permission;
    }

    public String getSource(){
        return this.src_ip;
    }

    public String getSourceMask(){
        return this.src_mask;
    }

    public void printACL(){
        System.out.println("access-list  " + this.acl_num + "  " + this.permission + "  " + this.src_ip + "  " + this.src_mask);
    }
}