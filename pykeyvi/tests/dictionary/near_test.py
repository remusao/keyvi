# -*- coding: utf-8 -*-
# Usage: py.test tests

import contextlib
import os

import pykeyvi

import sys
import os

root = os.path.dirname(os.path.abspath(__file__))
sys.path.append(os.path.join(root, "../"))

from test_tools import tmp_dictionary

def test_near():
    c=pykeyvi.JsonDictionaryCompiler()
    c.Add("zahnarzt:u0we9yykdyum", '["a" : 2]')
    c.Add("zahnarzt:u1h2fde2kct3", '["a" : 3]')
    c.Add("zahnarzt:u1huf1q5cnxn", '["a" : 4]')
    c.Add("zahnarzt:u0y2dvey61sw", '["a" : 5]')
    c.Add("zahnarzt:u1hvqmmj801r", '["a" : 6]')
    c.Add("zahnarzt:u0vvmknrwgmj", '["a" : 7]')
    c.Add("zahnarzt:u0ypv22fb9q3", '["a" : 8]')
    c.Add("zahnarzt:u1qcvvw0hxe1", '["a" : 9]')
    c.Add("zahnarzt:u1xjx6yfvfz2", '["a" : 10]')
    c.Add("zahnarzt:u1q0gkqsenhf", '["a" : 11]')
    with tmp_dictionary(c, 'near_simple.kv') as d:
        assert(len(list(d.GetNear("zahnarzt:u1q0gkqsenhf", 12))) == 1)
        assert(len(list(d.GetNear("zahnarzt:u1h0gkqsenhf", 12))) == 3)
        assert(len(list(d.GetNear("zahnarzt:u1h0gkqsenhf", 13))) == 0)
        assert(len(list(d.GetNear("zahnarzt:u0h0gkqsenhf", 10))) == 4)

def test_near_greedy():
    c=pykeyvi.JsonDictionaryCompiler()
    c.Add("zahnarzt:u0we9yykdyum", '["a" : 2]')
    c.Add("zahnarzt:u1h2fde2kct3", '["a" : 3]')
    c.Add("zahnarzt:u1huf1q5cnxn", '["a" : 4]')
    c.Add("zahnarzt:u0y2dvey61sw", '["a" : 5]')
    c.Add("zahnarzt:u1hvqmmj801r", '["a" : 6]')
    c.Add("zahnarzt:u0vvmknrwgmj", '["a" : 7]')
    c.Add("zahnarzt:u0ypv22fb9q3", '["a" : 8]')
    c.Add("zahnarzt:u1qcvvw0hxe1", '["a" : 9]')
    c.Add("zahnarzt:u1xjx6yfvfz2", '["a" : 10]')
    c.Add("zahnarzt:u1q0gkqsenhf", '["a" : 11]')
    with tmp_dictionary(c, 'near_simple.kv') as d:
        assert(len(list(d.GetNear("zahnarzt:u1q0gkqsenhf", 12, True))) == 2)
        assert(len(list(d.GetNear("zahnarzt:u1h0gkqsenhf", 12, True))) == 3)
        assert(len(list(d.GetNear("zahnarzt:u1h0gkqsenhf", 13, True))) == 0)
        assert(len(list(d.GetNear("zahnarzt:u0h0gkqsenhf", 10, True))) == 10)

        greedy = [x.GetMatchedString() for x in d.GetNear("zahnarzt:u0h0gkqsenhf", 10, True)]
        non_greedy = [x.GetMatchedString() for x in d.GetNear("zahnarzt:u0h0gkqsenhf", 10, False)]
        assert greedy[:len(non_greedy)] == non_greedy


def test_near_less_precission():
    c=pykeyvi.JsonDictionaryCompiler()
    c.Add("zahnarzt:u0we9", '["a" : 2]')
    c.Add("zahnarzt:u1h2f", '["a" : 3]')
    c.Add("zahnarzt:u1huf", '["a" : 4]')
    with tmp_dictionary(c, 'near_simple.kv') as d:
        assert(len(list(d.GetNear("zahnarzt:u1h0gkqsenhf", 12))) == 2)
        assert(len(list(d.GetNear("zahnarzt:u1h0gkqsenhf", 13))) == 0)

def test_near_broken_input():
    c=pykeyvi.JsonDictionaryCompiler()
    c.Add("zahnarzt:u0we9", '["a" : 2]')
    c.Add("zahnarzt:u1h2f", '["a" : 3]')
    c.Add("zahnarzt:u1huf", '["a" : 4]')
    with tmp_dictionary(c, 'near_simple.kv') as d:
        assert(len(list(d.GetNear("zahnarzt:u1h", 12))) == 2)
        assert(len(list(d.GetNear("zahnarzt:u", 13))) == 0)
        assert(len(list(d.GetNear("zahnarzt:u1", 12))) == 0)

