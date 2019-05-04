#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ply.lex
import re
import web.template
import sys
import os
import math

class context(object):
    def __init__(self, ctx):
        self._ctx = ctx
    def __getattr__(self, name):
        name = name.lower()
        return self._ctx.get(name)


def parser(code, ctx):
    c=context(ctx)
    rt = web.template.Template(code, globals=globals(), builtins=__builtins__)(c)
    return rt.__body__
