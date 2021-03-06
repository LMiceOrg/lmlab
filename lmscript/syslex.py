#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ply.lex
#import re
import web.template
import sys

tokens = (
    "language",
    "code",

    "newline",
    "heading",
    "setext",
    "blockquotes",
    "unordered_list",
    "ordered_list",
    "content",
    "comment",
    "fileset",
)

states=(
    ('language', 'exclusive'),
)



#def t_space(t):
#    r"[ \t]{1,}"
#    t.value = t.value.count(" ") + 4* t.value.count("\t")
#    return t



def t_language(t):
    r"([/]{2,}|[#]{1,}|[$][#]{1,})[~]{3}(?P<language>\w+)\s*[~]{3}"
    t.lexer.type = t.lexer.lexmatch.group('language')
    t.lexer.code_start = t.lexer.lexpos        # Record the starting position
    t.lexer.level = 1                          # Initial brace level
    t.lexer.begin('language')                     # Enter 'ccode' state
    #return t

def t_language_code(t):
     r"([/]{2,}|[#]{1,}|[$][#]{1,})[~]{3}(?P<language>\w+)\s*[~]{3}"
     if t.lexer.lexmatch.group('language') != t.lexer.type:
         lineno = t.lexer.lexdata[:t.lexer.lexpos].count('\n')+1
         #print(t.lexer.lexmatch.group('language'), t.lexer.type)
         raise TypeError("language mismatch error %s, should be %s, at line %d[%d]"
            % (t.lexer.lexmatch.group('language'), t.lexer.type, lineno, t.lexer.lexpos) )
     t.lexer.level -=1
     # If closing brace, return the code fragment
     if t.lexer.level == 0:

        size =len(t.value)
        t.value = t.lexer.lexdata[t.lexer.code_start:t.lexer.lexpos-size]
#        if t.lexer.type == 'lmcpp':
#            t.value = web.template.Template(t.value)().__body__
#            t.lexer.type = 'cplusplus'
#        elif t.lexer.type == 'lmpython':
#            t.value = web.template.Template(t.value)().__body__
#            t.lexer.type = 'python'
        t.lexer.begin('INITIAL')
        return t

# For bad characters, we just skip over it
def t_language_error(t):
    t.lexer.skip(1)

def t_heading(t):
    r"(?P<heading>[#]{1,})(?P<ctx>[^\n#]*)(?P=heading){0,1}\n"
    t.value =t.lexer.lexmatch.group('ctx')
    t.lexer.level = len(t.lexer.lexmatch.group("heading"))
    return t

def t_setext(t):
    r"(?P<ctx>[^#\n]+)\n\s*(?P<heading>[=]{1,}|[-]{1,})\s*\n"
    t.type = "heading"
    t.value =t.lexer.lexmatch.group('ctx')
    if t.lexer.lexmatch.group("heading")[0] == '=':
        t.lexer.level = 1
    else:
        t.lexer.level = 2
    #t.lexer.level = len(t.lexer.lexmatch.group("heading"))
    return t

def t_blockquotes2(t):
    r"(?P<block>[>]{1,})(?P<ctx>([^>\n]+[\n]){1,})[\n]"
    t.type = "blockquotes"
    t.lexer.level = len(t.lexer.lexmatch.group("block"))
    t.value = t.lexer.lexmatch.group('ctx')
    return t

def t_blockquotes1(t):
    r"(?P<block>[>]{1,})(?P<ctx>.*)[\n]"
    t.type = "blockquotes"
    t.lexer.level = len(t.lexer.lexmatch.group("block"))
    t.value = t.lexer.lexmatch.group('ctx')
    return t

def t_unordered_list(t):
    r"(?P<label>[*+-])\s+(?P<ctx>.*)"
    t.value = t.lexer.lexmatch.group('ctx')
    return t

def t_ordered_list(t):
    r"(?P<label>[0-9]+[.])\s+(?P<ctx>.*)"
    t.value = t.lexer.lexmatch.group('ctx')
    return t

def t_newline(t):
    r"\n+"
    cnt = len(t.value)
    t.lexer.lineno += cnt
    if cnt >=2:
        return t

def t_comment(t):
    r"(comment|注释)[:：].*"
    return t

def t_fileset(t):
    r'(?P<name>\w+)\s*[=]\s*from\s+["](?P<folder>[^"]+)["]\s+import\s+[(](?P<date>[^)]+)[)]\s+(?P<type>\w+)\s+[[](?P<code>[^]]+)[]]'
    t.fname = t.lexer.lexmatch.group("name")
    t.ffolder = t.lexer.lexmatch.group("folder")
    t.fdate = t.lexer.lexmatch.group("date")
    t.fcode = t.lexer.lexmatch.group("code")
    t.ftype = t.lexer.lexmatch.group("type")
    return t


def t_content(t):
    r".+"
    return t

def t_error(t):
    raise TypeError("Unknown text '%s'" % (t.value,))

ply.lex.lex()

#ply.lex.input("""
###~~~python~~~
#def add(a,b):
#    return a+b

###~~~python~~~

#//~~~cplusplus~~~
#int add(int a, int b)
#{
#    return a+b
#}

#//~~~cplusplus~~~

#$#~~~lmpython~~~

#<html>
#</html>

#$#~~~lmpython~~~

#$#~~~lmcpp~~~

#int vec_add(b,c)
#{
#    int a[10];
#    $for i in range(10):
#        $:('a[%d] = b[%d]*c[%d];' % (i,i,i))

#    int result = 0;
#    $for i in range(10):
#        result += a[$:(i)];

#    return result;
#}

#$#~~~lmcpp~~~

### welcome to home

#my name is hehao
#this is bnug

#heading 3
#========
#heading 2
#--

#> quote >  1
#>> quote 2
#> quote1
#aaa bb
#cc dd
#eee ffff



#aa

## 列表

#* a
#* b
#* c

## 有序列表

#1. aa
#2. bb
#3. cc

#""")

class fileset(object):
    name=""
    type=""
    folder=""
    date=""
    code=""
    def __repr__(self):
        return '<fileset: %s> %s' % (self.type, self.name)

def show_lex(name):
    f=open(name,'r', encoding='utf-8')
    source = f.read()
    f.close()
    ply.lex.input(source)

    import math

    ctx=dict()
    ctx['dir']= dir
    ctx['math']= math

    for tok in iter(ply.lex.token, None):
        if tok.type == "heading":
            print( repr(tok.type), repr(tok.value), repr(tok.lexer.level) )
        elif tok.type == "code":
            print( repr(tok.type), repr(tok.lexer.type) )
            #print(tok.value)
            if tok.lexer.type == 'lmpython':
                import lmpython
                print( lmpython.parser(tok.value.lstrip(), ctx) )
            elif tok.lexer.type == 'lmcpp':
                #print (tok.value)
                import lmpython
                print( lmpython.parser(tok.value.lstrip(), ctx) )
        elif tok.type == "fileset":
            print( repr(tok.type), repr(tok.value) )
            print("\t", repr(tok.ftype), repr(tok.fname),repr(tok.ffolder))
            fs = fileset()
            fs.name = tok.fname
            fs.type = tok.ftype
            fs.folder = tok.ffolder
            fs.date = tok.fdate.split(',')
            fs.code = tok.fcode.split(',')
            ctx[fs.name]=fs

        else:
            print( repr(tok.type), repr(tok.value) )

if __name__ == "__main__":
    if len(sys.argv)==1:
        print("usage: syslex.py <lms file>")
        show_lex("example.lms")
    else:
        show_lex(sys.argv[1])
