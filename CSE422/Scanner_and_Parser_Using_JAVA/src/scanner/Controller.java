package scanner;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.paint.Paint;
import javafx.scene.web.WebView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.stream.Stream;

public class Controller {

    public Label resultLabel;
    public TextField sourceFileTextField;
    public TextField outputPathTextField;
    public Button compileButton;
    public Button openInBrowser;
    public WebView webView;
    private File sourceFile;
    private parser.Controller parser;

    public void getSourceFilePath() {
        File outputFile;
        compileButton.setDisable(true);
        openInBrowser.setDisable(true);
        resultLabel.setText("");
        resultLabel.setTextFill(Paint.valueOf("RED"));
        String sourceFilePath = sourceFileTextField.getText().trim();
        sourceFile = new File(sourceFilePath);
        if(!sourceFile.exists()) {
            resultLabel.setText("Source File does NOT Exist!");
            return;
        }
        if(!sourceFile.isFile()) {
            resultLabel.setText("Source File is NOT a File!");
            return;
        }
        File inputFileParent = sourceFile.getParentFile();
        String outputPath = inputFileParent.getAbsolutePath()  + "\\result.txt";
        outputPathTextField.setText(outputPath);
        outputFile = new File(outputPath);
        try {
            outputFile.createNewFile();
        } catch (IOException e) {
            resultLabel.setText("ERROR: " + e.getMessage());
            return;
        }
        if(!outputFile.canWrite()) {
            resultLabel.setText("Output File is NOT a Writable File!");
            return;
        }
        compileButton.setDisable(false);
    }

    public void startScanning() throws IOException {
        resultLabel.setText("Start Scanning...");
        PrintStream out = new PrintStream(new FileOutputStream(outputPathTextField.getText()));
        System.setOut(out);

        ArrayList<ArrayList<String>> tokensArrayList = new ArrayList<>();

        for(Token t : Scanner.scan(readLineByLine(sourceFile.getPath()))) {
            System.out.println(t.getValue() + ", " + t.getType());
            ArrayList<String> tokenArrayList = new ArrayList<>();
            tokenArrayList.add(t.getValue());
            tokenArrayList.add(t.getType());
            tokensArrayList.add(tokenArrayList);
        }

        resultLabel.setTextFill(Paint.valueOf("GREEN"));
        resultLabel.setText("Scanning Done.");

        parser = new parser.Controller();
        parser.startParsing(this.webView, tokensArrayList, resultLabel);
        openInBrowser.setDisable(false);
    }

    private static String readLineByLine(String filePath)
    {
        StringBuilder contentBuilder = new StringBuilder();
        try (Stream<String> stream = Files.lines( Paths.get(filePath), StandardCharsets.UTF_8))
        {
            stream.forEach(s -> contentBuilder.append(s).append("\n"));
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        return contentBuilder.toString();
    }

    public void openInBrowser() {
        parser.openInBrowser();
    }
}
