import unittest

from abem.schedules import act


class TestSchedules(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.xcoord1 = 123
        self.ycoord1 = 456.7
        self.xcoord2 = 235
        self.ycoord2 = 567.8

    def test_200(self):
        """ Point_Final """
        activity = act.Point_Final("test_200", self.xcoord1, self.ycoord1)

        self.assertEqual(activity.xcoord, self.xcoord1)
        self.assertEqual(activity.ycoord, self.ycoord1)

    def test_201(self):
        """ Point_Fixed """
        activity = act.Point_Fixed("test_201", self.xcoord1, self.ycoord1, 240)

        self.assertEqual(activity.xcoord, self.xcoord1)
        self.assertEqual(activity.ycoord, self.ycoord1)
        self.assertEqual(activity.duration, 240)

    def test_300(self):
        """ Buffer_Final """
        activity = act.Buffer_Final("test_300", self.xcoord1, self.ycoord1, 150)

        self.assertEqual(activity.xcoord, self.xcoord1)
        self.assertEqual(activity.ycoord, self.ycoord1)
        self.assertEqual(activity.buffersize, 150)

    def test_301(self):
        """ Buffer_Fixed """
        activity = act.Buffer_Fixed("test_301", self.xcoord1, self.ycoord1, 150, 240)

        self.assertEqual(activity.xcoord, self.xcoord1)
        self.assertEqual(activity.ycoord, self.ycoord1)
        self.assertEqual(activity.buffersize, 150)
        self.assertEqual(activity.duration, 240)


    def test_400(self):
        """ Commute """
        activity = act.Commute("test_400", self.xcoord1, self.ycoord1, self.xcoord2, self.ycoord2, "car", 240)

        self.assertEqual(activity.start_x, self.xcoord1)
        self.assertEqual(activity.start_y, self.ycoord1)
        self.assertEqual(activity.dest_x, self.xcoord2)
        self.assertEqual(activity.dest_y, self.ycoord2)
        self.assertEqual(activity.duration, 240)