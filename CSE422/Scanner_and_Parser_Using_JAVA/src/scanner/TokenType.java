package scanner;

import java.util.ArrayList;
import java.util.Arrays;

public class TokenType {

    private String type;
    private static boolean CASE_SENSETIVE = false;

    TokenType(String value) {
        this.type = findTokenType(value);
    }

    public TokenType(TYPE text){
        this.type = text.toString();
    }

    private String findTokenType(String value){
        String type;
        if(!CASE_SENSETIVE) value = value.toLowerCase();
        if(value.matches("[0-9]*"))
            type = TYPE.NUMBER.toString();
        else if(RESEVED_WORDS.contains(value))
            type = TYPE.RESERVED_WORD.toString();
        else if(SPECIAL_SYMBOLS.contains(value))
            type = TYPE.SPECIAL_SYMBOL.toString();
        else if(value.equals(ASSIGN_SYMBOL))
            type = TYPE.ASSIGN.toString();
        else
            type = TYPE.IDENTIFIER.toString();
        return type;
    }

    String getType() {
        return type;
    }


    public enum TYPE{
        RESERVED_WORD,
        SPECIAL_SYMBOL,
        NUMBER,
        IDENTIFIER,
        ASSIGN
    }

    private static final ArrayList<String> RESEVED_WORDS = new ArrayList<>(
        Arrays.asList(
            "if", "then", "else", "end",
            "repeat", "until",
            "read", "write"
        )
    );

    private static final ArrayList<String> SPECIAL_SYMBOLS = new ArrayList<>(
        Arrays.asList(
            "+","-","*","/",
            "=", "<",
            "(",")",";"
        )
    );

    private static final String ASSIGN_SYMBOL = ":=";

    @Override
    public boolean equals(Object o){
        return (
            o != null &&
            o instanceof TokenType &&
            this.type.equals(((TokenType) o).type)
        );
    }

    @Override
    public int hashCode(){
        return this.type.hashCode();
    }
}
