import unittest
from surfkini import ramp_classify

class TestCollisionDetection(unittest.TestCase):
    def test_ramp_collision(self):
        # Test ramp collision detection
        self.assertEqual(ramp_classify("ramp"), "ramp")
        self.assertNotEqual(ramp_classify("floor"), "ramp")
        self.assertNotEqual(ramp_classify("wall"), "ramp")

    def test_floor_collision(self):
        # Test floor collision detection
        self.assertEqual(ramp_classify("floor"), "floor")
        self.assertNotEqual(ramp_classify("ramp"), "floor")
        self.assertNotEqual(ramp_classify("wall"), "floor")

    def test_wall_collision(self):
        # Test wall collision detection
        self.assertEqual(ramp_classify("wall"), "wall")
        self.assertNotEqual(ramp_classify("ramp"), "wall")
        self.assertNotEqual(ramp_classify("floor"), "wall")

if __name__ == '__main__':
    unittest.main()