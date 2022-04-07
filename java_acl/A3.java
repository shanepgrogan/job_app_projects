import java.io.*;
import java.util.*;

public class A3{

    public static void main(String[] args){
        
        ArrayList<Standard_ACL> std_acl_list = new ArrayList<Standard_ACL>();
        ArrayList<Standard_Packet> std_packet_list = new ArrayList<Standard_Packet>();

        ArrayList<Extended_ACL> ext_acl_list = new ArrayList<Extended_ACL>();
        ArrayList<Extended_Packet> ext_packet_list = new ArrayList<Extended_Packet>();

        try{

            // Standard ACL Program
            
            File file1 = new File("std_acl_input.txt");
            File file2 = new File("std_packet_input.txt");

            Scanner s1 = new Scanner(file1);
            Scanner s2 = new Scanner(file2);

            while(s1.hasNextLine()){
                
                String line = s1.nextLine();
                String[] splitLine = line.split(" ");
                
                if(splitLine[0].equals("access-list")){
                    
                    Standard_ACL acl;

                    int acl_num = Integer.parseInt(splitLine[1]);
                    String perm = splitLine[2];
                    String src = splitLine[3];
                    String src_mask = splitLine[4];
                    
                    acl = new Standard_ACL(acl_num, perm, src, src_mask);

                    std_acl_list.add(acl);
                    
                }
                
            }
            s1.close();

            for(Standard_ACL acl : std_acl_list){
                acl.printACL();
            }

            while(s2.hasNextLine()){
                
                String line = s2.nextLine();
                String[] splitLine = line.split(" ");
                String src = splitLine[0];

                Standard_Packet packet = new Standard_Packet(src);

                std_packet_list.add(packet);

            }
            s2.close();

            Standard_ACL_Program std_acl_pgm = new Standard_ACL_Program(std_acl_list, std_packet_list);

            for(Standard_Packet packet : std_acl_pgm.get_packet_list()){

                std_acl_pgm.verifyPacket(packet);

            }

            System.out.println();

            // Extended ACL Program

            File file3 = new File("ext_acl_input.txt");
            File file4 = new File("ext_packet_input.txt");

            Scanner s3 = new Scanner(file3);
            Scanner s4 = new Scanner(file4);

            while(s3.hasNextLine()){
                
                String line = s3.nextLine();
                String[] splitLine = line.split(" ");
                
                if(splitLine[0].equals("access-list")){
                    
                    Extended_ACL acl;

                    int acl_num = Integer.parseInt(splitLine[1]);
                    String perm = splitLine[2];
                    String protocol = splitLine[3];
                    String src = splitLine[4];
                    String src_mask = splitLine[5];
                    String dest = splitLine[6];
                    String dest_mask = splitLine[7];
                    
                    if(splitLine.length > 8){
                        
                        String port_range_str = splitLine[9];
                        String[] range_limits = port_range_str.split("-");
                        int l1 = Integer.parseInt(range_limits[0]);
                        int l2 = Integer.parseInt(range_limits[1]);
                        ArrayList<Integer> port_range = new ArrayList<Integer>();
                        
                        for(int i = l1; i <= l2; i++){
                            port_range.add(i);
                        }
                        
                        acl = new Extended_ACL(acl_num, perm, src, src_mask, dest, dest_mask, protocol, port_range);
                    
                    } else {
                    
                        acl = new Extended_ACL(acl_num, perm, src, src_mask, dest, dest_mask, protocol);
                    
                    }

                    ext_acl_list.add(acl);
                
                }

            }
            
            s3.close();

            for(Extended_ACL acl : ext_acl_list){
                acl.printACL();
            }

            while(s4.hasNextLine()){
                
                String line = s4.nextLine();
                String[] splitLine = line.split(" ");
                String src = splitLine[0];
                String dest = splitLine[1];
                String port_str = splitLine[2];
                int port = Integer.parseInt(port_str);

                Extended_Packet packet = new Extended_Packet(src, dest, port);

                ext_packet_list.add(packet);

            }
            s4.close();
        
        } catch(FileNotFoundException e){
            System.out.println("Error: File not found!");
        }

        Extended_ACL_Program ext_acl_pgm = new Extended_ACL_Program(ext_acl_list, ext_packet_list);

        for(Extended_Packet packet : ext_acl_pgm.get_packet_list()){
        
            ext_acl_pgm.verifyPacket(packet);

        }

    }

}