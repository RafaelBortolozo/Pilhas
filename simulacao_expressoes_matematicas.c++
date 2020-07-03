a) "(A+B})"

1- push("(") //pilha: (
2- stacktop()=="{" ?
    -false
    -expressao invalida!

b) "{[A + B] - [(C - D)]"

1- push("{") //pilha: {
2- push("[") //pilha: { [
3- stacktop()=="[" ?
    -true
    -pop()   //pilha: {
4- push("[") //pilha: { [
5- push("(") //pilha: { [ (
6- stacktop()=="(" ?
    -true
    -pop()   //pilha: { [
7- stacktop()=="[" ?
    -true
    -pop()   //pilha: {
8- pilha->size==0 ?
    -false
    -expressao invalida!

c) "(A + B)-{C + D}-[F+ G]"

1- push("(") //pilha: (
2- stacktop()=="(" ?
    -true
    -pop()   //pilha:
3- push("{") //pilha: {
4- stacktop()=="{" ?
    -true
    -pop()   //pilha:
5- push("[") //pilha: [
6- stacktop()=="[" ?
    -true
    -pop()   //pilha:
7- pilha->size==0 ?
    -true
    -expressao valida!

d) "((H) * {([J + K])})"

1- push("(") //pilha: (
2- push("(") //pilha: ( (
3- stacktop()=="(" ?
    -true
    -pop()   //pilha: (
4- push("{") //pilha: ( {
5- push("(") //pilha: ( { (
6- push("[") //pilha: ( { ( [
7- stacktop()=="[" ?
    -true
    -pop()   //pilha: ( { (
8- stacktop()=="(" ?
    -true
    -pop()   //pilha: ( {
9- stacktop()=="{" ?
    -true
    -pop()   //pilha: (
10- stacktop()=="(" ?
    -true
    -pop()   //pilha:
11- pilha->size==0 ?
    -true
    -expressao valida!

e) "(((A))))"

1- push("(") //pilha: (
2- push("(") //pilha: ( (
3- push("(") //pilha: ( ( (
4- stacktop()=="(" ?
    -true
    -pop()   //pilha: ( (
5- stacktop()=="(" ?
    -true
    -pop()   //pilha: (
6- stacktop()=="(" ?
    -true
    -pop()   //pilha:
7- stacktop()=="(" ?
    -false   
    -expressao invalida!
