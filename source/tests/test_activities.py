import unittest

from python.schedules import act


class TestSchedules(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.xcoord = 123
        self.ycoord = 456.7

    def test_200(self):
        """ Point_Final """
        activity = act.Point_Final("test_200", self.xcoord, self.ycoord)

        self.assertEqual(activity.xcoord, self.xcoord)
        self.assertEqual(activity.ycoord, self.ycoord)

    def test_201(self):
        """ Point_Fixed """
        activity = act.Point_Fixed("test_201", self.xcoord, self.ycoord, 240)

        self.assertEqual(activity.xcoord, self.xcoord)
        self.assertEqual(activity.ycoord, self.ycoord)
        self.assertEqual(activity._activity_delta, 240)
