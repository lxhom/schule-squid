# compile with coffee -b -c CtoCS.coffee and load it in node with .load CtoCS.js or copy the js file into a browser console
# or run coffee -b -c -w *.coffee in the VS Code Terminal and split *.coffee and and *.js

# c++ rand() function
rand = () -> Math.floor Math.random()  * 2 ** 16

# try to print all results
getAllResults = (func, iterations) ->
    if typeof func is "string"
        func = new Function "return " + func
    out = []
    for [0...iterations]
        output = func()
        out.push output unless out.includes output
    return out.sort()