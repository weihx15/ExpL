package com.compiler.expl;

class Interpreter implements Expr.Visitor<Object> {
    @Override
    public Object visitLiteralExpr(Expr.Literal expr) {
        return Double.parseDouble(String.valueOf(expr.value));
    }

    @Override
    public Object visitGroupingExpr(Expr.Grouping expr) {
        return evaluate(expr.expression);
    }

    private Object evaluate(Expr expr) {
        return expr.accept(this);
    }

    @Override
    public Object visitBinaryExpr(Expr.Binary expr) {
        Object left = evaluate(expr.left);
        Object right = evaluate(expr.right);

        return switch (expr.operator.type) {
            case PLUS -> (double) left + (double) right;
            case MINUS -> (double) left - (double) right;
            case STAR -> (double) left * (double) right;
            case SLASH -> (double) left / (double) right;
            default ->
                // Unreachable.
                    null;
        };
    }

    @Override
    public Object visitUnaryExpr(Expr.Unary expr) {
        Object right = evaluate(expr.right);

        return -(double) right;
    }

    void interpret(Expr expression) {
        Object value = evaluate(expression);
        System.out.println(stringify(value));
    }

    private String stringify(Object object) {
        String text = object.toString();
        if (text.endsWith(".0")) {
            text = text.substring(0, text.length() - 2);
        }

        return text;
    }
}
