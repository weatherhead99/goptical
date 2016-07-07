# -*- coding: utf-8 -*-
"""
Created on Tue Jun 21 14:06:13 2016

@author: weatherill
"""

from __future__ import (absolute_import, print_function, unicode_literals, division)

testfile = "THORLABS.ZMF"

from struct import Struct
import os
import io
from enum import Enum
import numpy as np
from collections import namedtuple
import math

Lens = namedtuple("Lens",["name","shape","elements","aspheric","version","grin","toroidal","efl","enp","description"])






class ZMFReader(object):
    SUPPORTED_VERSIONS = [1001]
    lens_struct = Struct("<100sIIIIIIIdd")
    shapes = { 0 : "?" ,
              1 : "E",
              2 : "B",
              3 : "P",
               4 : "M"}
    def __init__(self,fname):
        self._stream_handle(fname, self._lens_readall_fun)
            
    def _stream_handle(self,fname,fun,funargs=()):
	with io.open(fname,"rb") as f:
            head = Struct("<I")
            version = head.unpack(f.read(4))
            self.version = version[0]
            if self.version not in self.SUPPORTED_VERSIONS:
                raise IndexError("unsupported ZMF file version")
            fun(f,*funargs)
        
    def _lens_readall_fun(self,f):
	self.lenses = []
	while True:
	  ln = self._read_lens_struct(f)
	  if ln is None:
	    break
	  
	  self.lenses.append(ln)
            
    def _read_lens_struct(self,strm,return_desc_raw=False):
        
        data = strm.read(self.lens_struct.size)        
        if data == u'' :
            return None
        
        l = self.lens_struct.unpack(data)
        
        #print("description length:" + str(l[7]))
        
        desc_raw = strm.read(l[7])        
        
        assert len(desc_raw) == l[7]
        
        lens = Lens( name= l[0].decode("latin1").strip("\0"),
                    shape= self.shapes[l[3]], 
                    elements = l[2],
                    aspheric= l[4],
                    version = l[1],
                    grin = l[5],
                    toroidal= l[6],
                    efl = l[8],
                    enp = l[9],
                    description = self.zmf_obfuscate(desc_raw,l[8],l[9]))
                                            
        if(return_desc_raw):
	  return lens,desc_raw
	
        return lens
        
    def zmf_obfuscate(self,data, a, b):
        iv = np.cos(6*a + 3*b)
        iv = np.cos(655*(np.pi/180)*iv) + iv
        p = np.arange(len(data))
        k = 13.2*(iv + np.sin(17*(p + 3)))*(p + 1)
        k = (int(("{:.8e}".format(_))[4:7]) for _ in k)
        data = np.fromstring(data, np.uint8)
        data ^= np.fromiter(k, np.uint8, len(data))
        return data.tostring()
        
        
class ZMFReader_debug(ZMFReader):
    def __init__(self,fname,n):
	self._stream_handle(fname, self._lens_rawdesc_fun, [n])
      
    def _lens_rawdesc_fun(self,f,n):
      
	#discard n lenses
	for i in xrange(n):
	    self._read_lens_struct(f)
	    
	self.ln,self.rawdesc = self._read_lens_struct(f,True)
	   

def format_places(num):
    k = int("{:.8e}".format(num)[4:7])
    return k


def numeric_places(num):
    #first range it into 0--1
    places = int(math.ceil(math.log10(num)))
    num /= 10**places
        
    k = num * 1E3
    f = math.modf(k)[0]
    f2 = math.modf(f * 1E3)[1]
    return int(f2)

if __name__ == "__main__":
    #an  = ZMFReader(testfile)
    
    #l = an.lenses[2]
    #print(l.description)
    
    an = ZMFReader_debug(testfile,2)
    
    print(an.ln.description)
    
    ords = map(ord, an.rawdesc)
    print(ords)
    
#    strs = an.ln.description.split("\n")
#    for s in strs:
#        print(s)

        
        
        
