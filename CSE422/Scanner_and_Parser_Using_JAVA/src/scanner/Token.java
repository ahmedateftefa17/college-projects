package scanner;

public class Token {

    private TokenType type;
    private String value;

    public Token(String text){
        this.type = new TokenType(text);
        this.value = text;
    }

    public Token(String text, TokenType type){
        this.type = type;
        this.value = text;
    }

    public String getType() {
        return type.getType();
    }

    public String getValue() {
        return value;
    }

    @Override
    public boolean equals(Object o){
        return (
            o != null &&
            o instanceof Token &&
            this.type.equals(((Token) o).type) &&
            this.value.equals(((Token) o).value)
        );
    }

    @Override
    public int hashCode(){
        return this.type.hashCode() + this.value.hashCode();
    }
}
