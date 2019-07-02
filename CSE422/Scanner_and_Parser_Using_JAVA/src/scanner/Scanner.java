package scanner;

import java.util.ArrayList;

public class Scanner {

    private enum STATE{
        START,
        IN_COMMENT,
        IN_NUM,
        IN_ID,
        IN_ASSIGN
    }

    private static ArrayList<Token> Tokens = new ArrayList<>();

    private static final String WHITE_SPACE = "\\s";
    private static final String DIGIT = "[0-9]";
    private static final String LETTER = "[a-zA-Z_]";
    private static final String CURLY_BRACES_OPENING = "\\{";
    private static final String CURLY_BRACES_CLOSING = "\\}";
    private static final String COLON = ":";
    private static final String EQUAL = "=";

    private static StringBuilder tokenAccumulator = new StringBuilder();
    private static STATE currentState = STATE.START;

    public static ArrayList<Token> scan(String code) {
        String nextLetter;

        currentState = STATE.START;
        tokenAccumulator = new StringBuilder();
        Tokens = new ArrayList<>();

        code += " ";

        for(int counter = -1; counter < code.length() - 1; counter++){
            nextLetter = Character.toString(code.charAt(counter+1));

            switch(currentState) {
                case START:
                    tokenAccumulator = new StringBuilder();
                    if (nextLetter.matches(WHITE_SPACE)) {
                        currentState = STATE.START;
                    } else if (nextLetter.matches(CURLY_BRACES_OPENING)) {
                        currentState = STATE.IN_COMMENT;
                    } else if (nextLetter.matches(DIGIT)) {
                        tokenAccumulator.append(nextLetter);
                        currentState = STATE.IN_NUM;
                    } else if (nextLetter.matches(LETTER)) {
                        tokenAccumulator.append(nextLetter);
                        currentState = STATE.IN_ID;
                    } else if (nextLetter.matches(COLON)) {
                        tokenAccumulator.append(nextLetter);
                        currentState = STATE.IN_ASSIGN;
                    } else {
                        tokenAccumulator.append(nextLetter);
                        setDoneState(nextLetter);
                    }
                    break;
                case IN_COMMENT:
                    if (nextLetter.matches(CURLY_BRACES_CLOSING))
                        currentState = STATE.START;
                    break;
                case IN_NUM:
                    if (nextLetter.matches(DIGIT)) {
                        currentState = STATE.IN_NUM;
                        tokenAccumulator.append(nextLetter);
                    } else {
                        setDoneState(nextLetter);
                        counter--;
                    }
                    break;
                case IN_ID:
                    if (nextLetter.matches(LETTER) || nextLetter.matches(DIGIT)) {
                        currentState = STATE.IN_ID;
                        tokenAccumulator.append(nextLetter);
                    } else {
                        setDoneState(nextLetter);
                        counter--;
                    }
                    break;
                case IN_ASSIGN:
                    if (nextLetter.matches(EQUAL)){
                        tokenAccumulator.append(nextLetter);
                    }
                    setDoneState(nextLetter);
                    break;
            }
        }
        return Tokens;
    }

    private static void setDoneState(String currentLetter){
        if(!tokenAccumulator.toString().replaceAll("\\s+","").equals(""))
            Tokens.add(new Token(tokenAccumulator.toString().trim()));
        currentState = STATE.START;
        tokenAccumulator = new StringBuilder();
    }
}