# Squid documentation

## This section covers the following files:
- [coffeedebug/CtoCS.coffe](/coffeedebug/CtoCS.coffee)
- [coffeedebug/CtoCS.js](/coffeedebug/CtoCS.js)

------

This is a CoffeScript used to test the behaviour of new C++ features. It has 2 functions:

------

## The `rand()` function

It defines the `rand` function to behave like the `rand` function from C++. It returns a random number between `0` and `2^16 - 1`, floored.

##### From [CtoCS.coffee](/coffeedebug/CtoCS.coffee)

```coffee
# c++ rand() function
rand = () -> Math.floor Math.random()  * 2 ** 16
```

------

## The `getAllResults()` function
It tries to get all results of a function with randomness.

The first argument is either a function or a string that gets converted into a function. The seccond argument indicates how often the function should be called.

The function does this:

- It checks if the type of the first argument is `string` and then converts into a function.

- Then it creates a output array.

- Now we execute the function as many times as the user wants to, and push the output of the function into the array unless the array includes output.

- Now we sort and return the array.

The CoffeeScript looks like this:

##### From [CtoCS.coffee](/coffeedebug/CtoCS.coffee)


```coffee
# try to print all results
getAllResults = (func, iterations) ->
    if typeof func is "string"
        func = new Function "return " + func
    out = []
    for [0...iterations]
        output = func()
        out.push output unless out.includes output
    return out.sort()
```

And if we compile it into JS (`coffee -b -c CtoCS.js`) we get this:

##### From [CtoCS.js](/coffeedebug/CtoCS.js)


```js
// c++ rand() function
var getAllResults, rand;

rand = function() {
  return Math.floor(Math.random() * 2 ** 16);
};

// try to print all results
getAllResults = function(func, iterations) {
  var i, out, output, ref;
  if (typeof func === "string") {
    func = new Function("return " + func);
  }
  out = [];
  for (i = 0, ref = iterations; (0 <= ref ? i < ref : i > ref); 0 <= ref ? i++ : i--) {
    output = func();
    if (!out.includes(output)) {
      out.push(output);
    }
  }
  return out.sort();
};
```

This can now be copied into a Browser JS Console or a NodeJS Console (with `.load coffeedebug/CtoCS.js`). Example:

```js
> .load coffeedebug/CtoCS.js
[...]
< [Function: getAllResults]

> rand()
< 27312

> getAllResults(function(){return rand()%5*1.5+1.5}, 30)
< [ 1.5, 3, 4.5, 6, 7.5 ]

> getAllResults(()=>rand()%2*2-1, 50)
< [ -1, 1 ]

> getAllResults("rand()%5+1",1000)
< [ 1, 2, 3, 4, 5 ]
```

------

###### Last documented commit: [586d39](https://github.com/lxhom/schule-squid/586d39d3f7d4195aa4af83e099135960afb38788)