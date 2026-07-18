#ifndef WMGR_BOILERPLATE_H
#define WMGR_BOILERPLATE_H

#ifndef WMGR_BOILERPLATE_DEFAULT_INDEX_HTMW
#define WMGR_BOILERPLATE_DEFAULT_INDEX_HTMW "<@include_once \"i.htmw\">\n\
<Page title={ APP.name } lang=\"en\">\n\
    <h1>Hello and welcome to <PrettyText><@{ APP.name }></PrettyText></h1>\n\
    <p>It works!</p>\n\
</Page>"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_CONFIG_HTMW
#define WMGR_BOILERPLATE_DEFAULT_CONFIG_HTMW "<@ntxt>\n\
<@area \"config\">\n\
\n\
<@ -> {\n\
    APP = {\n\
        name = \"%s\"\n\
    }\n\
}>\n\
\n\
<@template content(){}><body><@include \"configs/header.htmw\"><main class=\"content-pad\">$INNER</main></body></@template>\n\
\n\
</@area>\n\
</@ntxt>"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_HEADER_HTMW
#define WMGR_BOILERPLATE_DEFAULT_HEADER_HTMW "<@include_once \"configs/config.htmw\">\n<div style=\"width: 100%; height: 64px; background-color: black; padding: 10px; position: fixed; top: 0px; display: flex; align-items: center;\">\n\
    <span style=\"font-size: 25px; font-weight: bold; color: white;\"><@{ APP.name }></span>\n\
</div>\n\
<div style=\"height: 64px;\"></div>"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_STYLE_CSS
#define WMGR_BOILERPLATE_DEFAULT_STYLE_CSS "html, body {\n\
    font-family: Arial, Helvetica, sans-serif;\n\
    margin: 0px;\n\
}\n\
\n\
div {\n\
    box-sizing: border-box;\n\
}\n\
\n\
.content-pad {\n\
    max-width: 900px;\n\
    padding: 0px 10px;\n\
    margin: 0 auto;\n\
}\n\
\n\
.pretty-text {\n\
    width: fit-content;\n\
    position: relative;\n\
    background: -webkit-linear-gradient(-30deg, rgb(37, 179, 255), rgb(171, 37, 255));\n\
    -webkit-background-clip: text;\n\
    -webkit-text-fill-color: transparent;\n\
    z-index: 1;\n\
}"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_MAKE_TXT
#define WMGR_BOILERPLATE_DEFAULT_MAKE_TXT "cc: %s;\n\
\n\
mod:\n\
    ;\n\
\n\
target:\n\
    index#html\n\
    style.css;\n\
\n\
assets:\n\
    assets>assets;\n\
\n\
out: out;\n\
src: src;\n\
build: build;\n\
dependencies: dependencies;"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_I_HTMW
#define WMGR_BOILERPLATE_DEFAULT_I_HTMW "<@ntxt>\n\
    <@area \"i\">\n\
        <@include_once \"configs/config.htmw\">\n\
        <@include_once \"templates/page_structure/Page.htmw\">\n\
        <@include_once \"templates/pretty/Text.htmw\">\n\
    </@area>\n\
</@ntxt>"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_PAGE_HTMW
#define WMGR_BOILERPLATE_DEFAULT_PAGE_HTMW "<@area \"page_structure:Page\">\n\
\n\
<@template Page(title, lang=\"en\", head?) {}>\n\
<!DOCTYPE html>\n\
<html lang=\"$lang\">\n\
<head>\n\
    <meta charset=\"UTF-8\">\n\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
    <title>$title</title>\n\
    <link rel=\"stylesheet\" href=\"/style.css\">\n\
    $head\n\
</head>\n\
<body>\n\
    <content>$INNER</content>\n\
    <Bottom/>\n\
</body>\n\
</html>\n\
</@template>\n\
\n\
<@template ninner Bottom() {}>\n\
<footer class=\"content-pad\">\n\
    <p>\n\
        wmgr by <a href=\"https://woxell.co\" target=\"_blank\">woxell.co</a>\n\
    </p>\n\
</footer>\n\
</@template>\n\
\n\
</@area>"
#endif

#ifndef WMGR_BOILERPLATE_DEFAULT_PRETTYTEXT_HTMW
#define WMGR_BOILERPLATE_DEFAULT_PRETTYTEXT_HTMW "<@area \"pretty:Text\">\n\
\n\
<@template dinner PrettyText(id?, style?, class?) {\n\
    local element = <span id={id} style={style} class=\"pretty-text\" data-text={INNER}>{INNER}</span>\n\
\n\
    if class then\n\
        element.props.class = \"pretty-text \" .. class\n\
    end\n\
}>$element</@template>\n\
\n\
</@area>"
#endif

#endif