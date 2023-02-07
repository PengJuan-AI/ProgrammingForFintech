import unittest
from max_seq.py import max_seq

class TestMaxSequence(unittest.TestCase):
    
    def test_TypeError(self):
        with self.assertRaises(Exception) as context:
            l = max_seq([1, 3, 5, 8,'a'])
        self.assertTrue(type(context.exception) == TypeError)

    def test_1(self):
        l = max_seq([1,1,1,1,1,1])
        self.assertEqual(l,[1])

    def test_empty(self):
        l = max_seq([])
        self.assertEqual(l,[])
