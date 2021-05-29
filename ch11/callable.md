# callables
`function object type`包括以下：

* pointer-to-function(including pointer-to-member-function/pointer-to-member-data)
* class with overloaded operator()
* class with a conversion function(pointer-to-function/reference-to-function)
* lambda expression

其实`function object`一般指的是第二类，因此我们用个描述性更好的词语：`callable`