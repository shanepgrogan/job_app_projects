import java.util.*;

public class Extended_Packet extends Standard_Packet{

    private String dest;
    private int port_num;

    Extended_Packet(String src, String dest, int port){
        super(src);
        this.dest = dest;
        this.port_num = port;
    }

    public String getDestination(){
        return this.dest;
    }

    public int getPortNumber(){
        return this.port_num;
    }

    public void printPacket(){
        System.out.println(this.getSource() + "   " + this.dest + "   " + this.port_num);
    }

}