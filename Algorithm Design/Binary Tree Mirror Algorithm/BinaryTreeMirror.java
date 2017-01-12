/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package binaryTreeMirror;
import java.util.*;
/**
 *
 * @author FRISCA
 */
// Java program to convert binary tree into its mirror
/* Class containing left and right child of current
   node and key value*/
class Node
{
    int data;
    Node left, right;
 
    public Node(int item)
    {
        data = item;
        left = right = null;
    }
}
class Binary_Tree_Mirror
{
    private static Node mirror(Node node)
    {
        Node m_root = null;
        if (node == null)
            return m_root;
        
        m_root = new Node(node.data);

        /* do the subtrees *//* swap the left and right pointers */
        m_root.left = mirror(node.right);
        m_root.right = mirror(node.left);

        return m_root;
    }

    // Encodes a tree to a single string.
    public static String serialize(Node root) {
        if (root == null) {
            return "";
        }

        Queue<Node> queue = new LinkedList<Node>();
        queue.offer(root);

        StringBuffer sb = new StringBuffer();

        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            if (curr != null) {
                sb.append(curr.data + ",");
                queue.offer(curr.left);
                queue.offer(curr.right);
            } else {
                sb.append("#" + ",");
            }
        }

        // Remove the trailing #
        int j = sb.length() - 1;
        while (j > 0 && (sb.charAt(j) == ',' && sb.charAt(j-1) == '#')) {
            j -= 2;
        }

        return "[" + sb.substring(0, j).toString().replace("#", "null") + "]";
    }

    // Decodes your encoded data to tree.
    public static Node deserialize(String data) 
    {
        if (data == null || data.length() == 0){
            return null;
        }
        if(data.startsWith("["))
            data = data.substring(1, data.length());
        if(data.endsWith("]"))
            data = data.substring(0, data.length()-1);

        data = data.replace(" ", ""); // omit any space
        data = data.replace("null", "#");

        Queue<Node> queue = new LinkedList<Node>();
        String[] nodes = data.split(",");

        Node root = new Node(Integer.parseInt(nodes[0]));
        queue.offer(root);
        int i = 1;

        while (!queue.isEmpty() && i < nodes.length) {
            Node curr = queue.poll();
            // left node
            if (nodes[i].equals("#")) {
                curr.left = null;
            } else {
                Node leftNode = new Node(Integer.parseInt(nodes[i]));
                curr.left = leftNode;
                queue.offer(leftNode);
            }

            i++;
            if (i >= nodes.length) {
                break;
            }

            // right node
            if (nodes[i].equals("#")) {
                curr.right = null;
            } else {
                Node rightNode = new Node(Integer.parseInt(nodes[i]));
                curr.right = rightNode;
                queue.offer(rightNode);
            }
            i++;
        }
        return root;
    }

    
 
    /* testing for example nodes */
    public static void main(String args[])
    {
        /* creating a binary tree and entering the nodes */
//        Node rootA = deserialize("[3,9,20,null,null,15,7]"); // case 1
         Node rootA = deserialize("[5,14,15,null,3,6,9,1]"); // case 2
//         Node rootA = deserialize("[3,20,9,null,null,1,5,2,4,null,null,15]"); // case 3
        //Experiment of 10
//        Node rootA = deserialize("[68, 75, 98, 31, 147, 194, 129, 100, 38, 4]");
        //50 nodes
//        Node rootA = deserialize("[76, 139, 40, 169, 99, 51, 59, 73, 147, 81, 41, 49, 162, 183, 24, 141, 92, "
//                + "25, 113, 122, 55, 87, 48, 120, 119, 35, 65, 44, 103, 102, 104, 53, 68, 39, 52, 192, 57, 185, "
//                + "178, 30, 4, 175, 58, 93, 27, 121, 149, 3, 77, 2]");
        //100 nodes
//        Node rootA = deserialize("[136, 132, 163, 126, 174, 46, 182, 118, 36, 120, 4, 172, 81, 129, 113, 190, "
//                + "23, 160, 71, 79, 152, 169, 45, 133, 135, 94, 115, 138, 84, 24, 55, 184, 10, 102, "
//                + "149, 63, 54, 68, 11, 192, 33, 30, 37, 40, 25, 67, 100, 21, 146, 130, 62, 189, 91, 39, "
//                + "103, 12, 191, 141, 117, 28, 92, 108, 107, 114, 47, 65, 6, 38, 16, 83, 9, 51, 197, 61, 89, "
//                + "50, 119, 112, 88, 121, 31, 93, 110, 66, 198, 72, 99, 69, 18, 43, 166, 125, 167, 53, 73, 183, "
//                + "153, 155, 17, 111]");
        //150 nodes
//        Node rootA = deserialize("[175, 158, 198, 85, 154, 131, 129, 95, 109, 84, 41, 23, 106, 196, 132, 57, 82,"
//                + " 91, 48, 143, 12, 29, 155, 5, 55, 17, 58, 7, 190, 139, 116, 63, 67, 146, 68, 162, 61, 88, 119,"
//                + " 138, 13, 14, 114, 152, 33, 8, 161, 145, 62, 191, 69, 186, 194, 125, 76, 20, 96, 134, 101, 123,"
//                + " 16, 100, 34, 148, 15, 112, 72, 56, 60, 150, 104, 193, 176, 117, 103, 28, 74, 37, 183, 187, 133,"
//                + " 136, 122, 18, 153, 167, 200, 127, 25, 31, 26, 168, 93, 81, 157, 180, 45, 27, 1, 135, 65, 50, 39,"
//                + " 19, 75, 59, 113, 174, 99, 11, 171, 172, 78, 36, 140, 164, 87, 90, 111, 102, 80, 137, 199, 40, 38,"
//                + " 54, 147, 83, 189, 51, 163, 77, 86, 115, 3, 73, 43, 128, 44, 107, 2, 47, 178, 195, 10, 35, 142, 170,"
//                + " 149, 197]");
        //200 nodes
//        Node rootA = deserialize("[103, 198, 86, 13, 21, 156, 101, 155, 38, 149, 180, 92, 49, 165, 19, 157, 109, 184,"
//                + " 60, 11, 95, 106, 81, 66, 44, 189, 70, 136, 125, 73, 52, 111, 78, 117, 186, 51, 89, 129, 175, 192,"
//                + " 122, 166, 76, 163, 72, 24, 30, 141, 42, 63, 161, 8, 41, 84, 29, 147, 178, 151, 94, 168, 123, 112,"
//                + " 10, 115, 104, 62, 7, 172, 15, 143, 142, 82, 171, 97, 98, 164, 126, 133, 18, 174, 182, 36, 39, 193,"
//                + " 1, 35, 113, 197, 57, 177, 26, 140, 32, 23, 91, 188, 199, 33, 110, 9, 65, 167, 6, 96, 144, 47, 77,"
//                + " 134, 176, 127, 90, 137, 80, 132, 99, 131, 160, 130, 116, 105, 185, 128, 17, 2, 45, 59, 93, 138, 102,"
//                + " 119, 107, 40, 14, 61, 88, 190, 162, 54, 69, 181, 28, 50, 146, 179, 169, 108, 75, 148, 46, 5, 195,"
//                + " 31, 145, 83, 191, 56, 16, 53, 67, 120, 194, 43, 150, 58, 173, 3, 48, 153, 196, 34, 170, 114, 187,"
//                + " 64, 158, 37, 79, 121, 159, 22, 25, 85, 152, 74, 55, 200, 124, 87, 118, 27, 183, 20, 154, 135, 68,"
//                + " 71, 139, 4, 100, 12]");
        //250 nodes
//        Node rootA = deserialize("[8, 9, 15, 100, 72, 5, 177, 185, 117, 213, 165, 43, 184, 58, 126, 147, 107, 188, 115,"
//                + " 30, 21, 110, 26, 236, 218, 175, 145, 226, 237, 119, 134, 17, 249, 41, 11, 171, 132, 112, 57, 133,"
//                + " 130, 27, 50, 212, 64, 140, 113, 247, 250, 246, 211, 229, 91, 106, 161, 125, 3, 96, 65, 227, 111,"
//                + " 86, 118, 16, 204, 76, 186, 174, 245, 82, 183, 153, 23, 10, 163, 173, 114, 225, 39, 2, 32, 222, 108,"
//                + " 235, 149, 202, 71, 192, 37, 28, 187, 234, 61, 1, 198, 80, 25, 137, 200, 102, 68, 116, 221, 20, 182,"
//                + " 154, 181, 248, 233, 158, 46, 73, 42, 224, 84, 99, 101, 156, 136, 242, 124, 138, 127, 141, 150, 207,"
//                + " 143, 29, 94, 63, 239, 104, 243, 45, 146, 164, 98, 157, 123, 97, 77, 142, 193, 75, 190, 109, 12, 162,"
//                + " 240, 19, 197, 14, 31, 217, 60, 74, 66, 195, 205, 152, 128, 176, 148, 83, 6, 93, 49, 206, 38, 189,"
//                + " 78, 56, 232, 180, 55, 196, 223, 62, 230, 191, 201, 139, 241, 85, 231, 228, 178, 34, 131, 220, 52,"
//                + " 13, 105, 54, 244, 214, 79, 24, 122, 47, 95, 81, 170, 103, 215, 210, 172, 144, 216, 69, 194, 36, 22,"
//                + " 59, 209, 35, 33, 18, 90, 7, 51, 40, 203, 167, 208, 160, 199, 168, 53, 135, 4, 159, 179, 67, 151, 70,"
//                + " 169, 88, 219, 166, 89, 120, 238, 121, 155, 44, 129, 87, 92, 48]");
                //300 nodes
//        Node rootA = deserialize("[198, 208, 23, 124, 22, 34, 219, 254, 153, 276, 175, 87, 241, 170, 238, 65, 190, 166,"
//                + " 30, 203, 195, 167, 39, 16, 233, 95, 77, 142, 82, 250, 157, 177, 221, 162, 185, 263, 189, 32, 183,"
//                + " 84, 217, 11, 187, 237, 78, 97, 125, 103, 134, 2, 146, 204, 100, 201, 259, 69, 277, 199, 57, 273, 5,"
//                + " 200, 48, 251, 180, 299, 222, 67, 244, 135, 74, 255, 286, 252, 172, 239, 279, 297, 138, 101, 141, 261,"
//                + " 85, 13, 21, 234, 147, 122, 71, 262, 28, 278, 14, 249, 99, 179, 148, 296, 295, 33, 44, 41, 19, 227,"
//                + " 139, 133, 6, 154, 256, 59, 42, 169, 110, 266, 267, 91, 193, 242, 163, 226, 223, 88, 20, 53, 40, 155,"
//                + " 292, 178, 27, 132, 184, 245, 269, 90, 300, 76, 3, 232, 117, 212, 25, 126, 72, 231, 15, 86, 4, 24, 38,"
//                + " 294, 136, 128, 36, 181, 225, 31, 161, 248, 51, 176, 94, 18, 109, 118, 236, 271, 112, 246, 61, 26, 207,"
//                + " 160, 272, 83, 210, 121, 258, 43, 211, 79, 49, 240, 58, 108, 243, 116, 115, 130, 290, 156, 70, 288,"
//                + " 158, 149, 230, 253, 52, 229, 7, 131, 151, 137, 152, 196, 260, 114, 282, 209, 129, 213, 63, 68, 105,"
//                + " 247, 143, 106, 188, 215, 113, 257, 174, 280, 281, 62, 64, 111, 192, 289, 119, 298, 291, 73, 80, 228,"
//                + " 274, 171, 284, 37, 173, 8, 1, 123, 9, 197, 140, 264, 287, 60, 191, 144, 12, 159, 104, 98, 235, 46,"
//                + " 293, 218, 54, 182, 10, 17, 55, 107, 270, 92, 268, 165, 216, 214, 220, 120, 102, 285, 206, 186, 194,"
//                + " 96, 35, 75, 56, 47, 205, 127, 150, 93, 168, 283, 81, 164, 265, 275, 224, 89, 50, 45, 66, 145, 202, 29]");

        /* Serialize the input tree */
        System.out.println("Test case 2");
        System.out.println("The given original tree is :");
        System.out.println(serialize(rootA));
        System.out.println("");
        long startCapturing = System.nanoTime();
        /* convert tree to its mirror */
        Node rootB = mirror(rootA);
 	long endCapturing = System.nanoTime();
        /* Serialize the input tree */
        System.out.println("The new serializing mirror tree is : ");
        System.out.println(serialize(rootB));
        System.out.println();
 	
        long time=(endCapturing-startCapturing)/1000;
        System.out.println("Experimenting Time Complexity is --> " + time + " Microseconds ");
    }
}
