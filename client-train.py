#!/usr/bin/env python
# -*- coding: utf-8 -*-

from jubatus.classifier.client import Classifier

port = 9199
timeout = 100

def main():
    client = Classifier("127.0.0.1", port, "sleeping", timeout)
    client.train([])

main()
