import unittest
import sys

import test_activities


if __name__ == "__main__":

    suite = unittest.TestSuite()
    suite.addTest(unittest.TestLoader().loadTestsFromModule(test_activities))

    result = unittest.TextTestRunner(verbosity=3).run(suite)
    test_result = (0 if result.wasSuccessful() else 1)

    sys.exit(test_result)
