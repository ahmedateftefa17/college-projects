package parser;

import javafx.scene.control.Label;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.awt.*;
import java.io.*;
import java.net.URI;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Stack;

public class Controller {

    private static final String GRAPH_HTML_PATH = "graph.html";
    private File HTMLFileTemp;

    public void startParsing(WebView webView, ArrayList<ArrayList<String>> tokensArrayList, Label label){
        try {
            label.setText("Start Parsing...");

            // Parents Stack
            Stack<Integer> parents = new Stack<>();
            parents.push(0);

            // Tokens to JSON List
            JSONArray tokensList = new JSONArray();

            // Loop over Tokens
            boolean inExp = false;
            boolean inSubExp = false;
            Stack<Integer> containersIds = new Stack<>();
            JSONObject token;
            for (int i = 0; i < tokensArrayList.size(); i++) {
                int id = i + 2;
                switch (tokensArrayList.get(i).get(1)) {
                    case "RESERVED_WORD":
                        switch (tokensArrayList.get(i).get(0).toLowerCase()) {
                            case "if":
                                token = new JSONObject();
                                token.put("id", id);
                                token.put("parentId", parents.peek());
                                token.put("name", "if");
                                tokensList.add(token);
                                parents.push(id);
                                containersIds.push(id);
                                inExp = true;
                                inSubExp = false;
                                break;
                            case "then":
                                break;
                            case "else":
                                while (!Objects.equals(parents.peek(), containersIds.peek())) {
                                    parents.pop();
                                }
                                break;
                            case "end":
                                while (!Objects.equals(parents.peek(), containersIds.peek()))
                                    parents.pop();
                                containersIds.pop();
                                break;
                            case "repeat":
                                token = new JSONObject();
                                token.put("id", id);
                                token.put("parentId", parents.peek());
                                token.put("name", "repeat");
                                tokensList.add(token);
                                parents.push(id);
                                containersIds.push(id);
                                break;
                            case "until":
                                while (!Objects.equals(parents.peek(), containersIds.peek()))
                                    parents.pop();
                                containersIds.pop();
                                inExp = true;
                                inSubExp = false;
                                break;
                            case "read":
                                // Token
                                token = new JSONObject();
                                token.put("id", id);
                                token.put("parentId", parents.peek());
                                i++;
                                token.put("name", "read " + tokensArrayList.get(i).get(0));
                                tokensList.add(token);
                                parents.push(id);
                                break;
                            case "write":
                                // Token
                                token = new JSONObject();
                                token.put("id", id);
                                token.put("parentId", parents.peek());
                                token.put("name", "write");
                                tokensList.add(token);
                                parents.push(id);
                                inExp = true;
                                inSubExp = false;
                                break;
                            default:
                                break;
                        }
                        break;
                    case "IDENTIFIER":
                    case "NUMBER":
                        // Negative
                        if(i - 2 >= 0 && tokensArrayList.get(i - 1).get(0).equals("-") && tokensArrayList.get(i - 2).get(1).equals("SPECIAL_SYMBOL"))
                            tokensArrayList.get(i).set(0, "-" + tokensArrayList.get(i).get(0));
                        // Assign
                        if (i + 1 < tokensArrayList.size() && tokensArrayList.get(i + 1).get(1).equals("ASSIGN")) {
                            token = new JSONObject();
                            token.put("id", id);
                            token.put("name", "assign " + tokensArrayList.get(i).get(0));
                            token.put("parentId", parents.peek());
                            tokensList.add(token);
                            parents.push(id);
                            inExp = true;
                        }
                        // Then
                        if (i + 1 < tokensArrayList.size() && tokensArrayList.get(i + 1).get(0).toLowerCase().equals("then")) {
                            token = new JSONObject();
                            token.put("id", id);
                            token.put("name", tokensArrayList.get(i).get(0));
                            token.put("parentId", parents.pop());
                            tokensList.add(token);
                            inExp = false;
                            inSubExp = false;
                        }
                        // SPECIAL_SYMBOL
                        if (inExp && i + 1 < tokensArrayList.size() && tokensArrayList.get(i + 1).get(1).equals("SPECIAL_SYMBOL")) {
                            switch (tokensArrayList.get(i + 1).get(0)) {
                                // )
                                case ")":
                                    token = new JSONObject();
                                    token.put("id", id);
                                    token.put("name", tokensArrayList.get(i).get(0));
                                    token.put("parentId", parents.peek());
                                    tokensList.add(token);
                                    break;
                                // ;
                                case ";":
                                    token = new JSONObject();
                                    token.put("id", id);
                                    token.put("name", tokensArrayList.get(i).get(0));
                                    token.put("parentId", parents.peek());
                                    tokensList.add(token);
                                    inExp = false;
                                    if (inSubExp) {
                                        parents.pop();
                                        inSubExp = false;
                                    }
                                    break;
                                // Operation + - * / < > =
                                default:
                                    token = new JSONObject();
                                    token.put("id", id + 1);
                                    token.put("name", "expression  " + tokensArrayList.get(i + 1).get(0));
                                    if (inSubExp)
                                        token.put("parentId", parents.pop());
                                    else
                                        token.put("parentId", parents.peek());
                                    tokensList.add(token);
                                    token = new JSONObject();
                                    token.put("id", id);
                                    token.put("name", tokensArrayList.get(i).get(0));
                                    token.put("parentId", id + 1);
                                    tokensList.add(token);
                                    parents.push(id + 1);
                                    inSubExp = true;
                                    break;
                            }
                        }
                        break;
                    case "SPECIAL_SYMBOL":
                        switch (tokensArrayList.get(i).get(0).toLowerCase()) {
                            case "+":
                            case "-":
                            case "*":
                            case "/":
                            case "=":
                            case "<":
                            case ">":
                            case ";":
                                break;
                            case "(":
                                int iTemp = i;
                                while (i < tokensArrayList.size()) {
                                    if (tokensArrayList.get(i).get(0).equals(")")) {
                                        id = i + 3;
                                        switch (tokensArrayList.get(i + 1).get(0)) {
                                            case "+":
                                            case "*":
                                            case "-":
                                            case "/":
                                            case "=":
                                            case ">":
                                            case "<":
                                                token = new JSONObject();
                                                token.put("id", id);
                                                token.put("name", "expression  " + tokensArrayList.get(i + 1).get(0));
                                                token.put("parentId", parents.pop());
                                                tokensList.add(token);
                                                parents.push(id);
                                                inSubExp = false;
                                                break;
                                            case ";":
                                            default:
                                                break;
                                        }
                                        break;
                                    }
                                    i++;
                                }
                                i = iTemp;
                                break;
                            case ")":
                                parents.pop();
                                break;
                            default:
                                break;
                        }
                        break;
                    case "ASSIGN":
                        break;
                    default:
                        break;
                }
            }



            // Define Final root
            JSONObject graphList = new JSONObject();
            graphList.put("hidden", true);
            graphList.put("children", tokensList);

            // JSON To String
            StringWriter out = new StringWriter();
            graphList.writeJSONString(out);
            String jsonText = out.toString();

            // Get Content of HTML
            ClassLoader classloader = Thread.currentThread().getContextClassLoader();
            InputStream is = classloader.getResourceAsStream(GRAPH_HTML_PATH);
            BufferedReader BR = new BufferedReader(new InputStreamReader(is));
            StringBuilder HTMLContent = new StringBuilder();
            String line;
            while ((line = BR.readLine()) != null)
                HTMLContent.append(line).append("\n");

            // Finalize Content
            String newHTMLContent = "<script type=\"text/javascript\">\n" +
                    "    var graphList = " + jsonText + ";\n" +
                    "</script>" +
                    HTMLContent;

            // Create Temp File
            HTMLFileTemp = File.createTempFile("ParserGraph", ".html");
            HTMLFileTemp.deleteOnExit();

            // Write to Temp File
            FileWriter fileWriter = new FileWriter(HTMLFileTemp.getAbsolutePath());
            fileWriter.write(newHTMLContent);
            fileWriter.close();

            // Create the WebEngine
            final WebEngine webEngine = webView.getEngine();
            // LOad the Start-Page
            webEngine.load("file:///" + HTMLFileTemp.getAbsolutePath());
            label.setText("Parsing Done");
        } catch(IOException e){
            e.printStackTrace();
        }
    }

    public void openInBrowser() {
        try {
            Desktop.getDesktop().browse(HTMLFileTemp.toURI());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
