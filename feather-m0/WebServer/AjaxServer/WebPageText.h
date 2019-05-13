//String htmlPage =
//  "<!DOCTYPE html> \n\
//<html lang=\"en\"> \n\
//<head>\n\
//    <meta charset=\"UTF-8\">\n\
//    <title>Title</title> \n\
//</head> \n\
//<body> \n\
//\n\
//<h1 id=\"id01\">DATA</h1> \n\
//<script> \n\
//\n\
//var xhr = new XMLHttpRequest(); \n\
//xhr.open('GET', \"http://10.0.0.1/data\", true); \n\
//    xhr.send();\n\
//    xhr.onreadystatechange = processRequest;\n\
//    var element = document.getElementById(\"id01\");\n\
//    function processRequest() \n\
//    {\n\
//        if (xhr.readyState == 4 && xhr.status == 200) \n\
//        { \n\
//            var response = xhr.responseText; \n\
//            console.log(response); \n\
//            element.innerHTML = response; \n\
//        } \n\
//    } \n\
//    setInterval(processRequest, 3000); \n\
//\n\
//</script> \n\
//</body>\n\
//</html>";

String htmlPage =
  "<!DOCTYPE html> \n\
<html lang=\"en\"> \n\
<head>\n\
    <meta charset=\"UTF-8\">\n\
    <title>Title</title> \n\
</head> \n\
<body> \n\
\n\
<h1 id=\"id01\">DATA</h1> \n\
<script> \n\
\n\
function repeatRequest()\n\
    {\n\
        var xhr = new XMLHttpRequest();\n\
        xhr.open('GET', \"http://10.0.0.1/data\");\n\
        xhr.responseType = \"document\";\n\
        xhr.send();\n\
        var element = document.getElementById(\"id01\");\n\
        xhr.onload = processRequest;\n\
\n\
        function processRequest()\n\
        {\n\
            element.innerHTML = xhr.response.body.innerText;\n\
        }\n\
    }\n\
    setInterval(repeatRequest, 500);\n\
\n\
</script> \n\
</body>\n\
</html>";


    
