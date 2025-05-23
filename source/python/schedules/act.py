from .config import ActivityType, ActivityDescription, CommuteType, BufferCalculation


class Activity(object):
    def __init__(self) -> None:

        self._time_delta = None
        self._end_time = None

        self._activity_type = ActivityType.unknown
        self._activity_description = ActivityDescription.unknown

        self._activity_id = None
        self._travel_mode = CommuteType.unknown

        self._activity_start = None
        self._activity_end = None

        self._agenda_start = None
        self._agenda_end = None

        self._position = None

    def activity(self, current_time):
        raise NotImplementedError

    @property
    def activity_type(self):
        return self._activity_type

    @property
    def activity_id(self):
        return self._activity_id

    @property
    def description(self):
        assert self._activity_description
        return self._activity_description

    @property
    def mode(self):
        assert self._travel_mode
        return self._travel_mode


class PointActivity(Activity):
    def __init__(self, act_desc: str) -> None:
        super().__init__()
        self._activity_type = ActivityType.point
        self._activity_description = act_desc

        self.xcoord = None
        self.ycoord = None


class BufferActivity(Activity):
    def __init__(self, act_desc: str) -> None:
        super().__init__()
        self._activity_type = ActivityType.buffer
        self._activity_description = act_desc

        self.xcoord = None
        self.ycoord = None
        self.buffersize = None
        self.buffer_method = BufferCalculation.unknown


class Point_Final(PointActivity):
    def __init__(self, act_desc: str, xcoord: int | float, ycoord: int | float) -> None:
        super().__init__(act_desc)

        self.xcoord = xcoord
        self.ycoord = ycoord

    def activity(self, current_time):

        assert self._agenda_start
        assert self._agenda_end

        self._activity_start = current_time
        self._activity_end = self._agenda_end


class Point_Fixed(PointActivity):
    def __init__(self, act_desc: str, xcoord: int | float, ycoord: int | float, duration: int) -> None:
        super().__init__(act_desc)

        self.xcoord = xcoord
        self.ycoord = ycoord
        self.duration = duration

    def activity(self, current_time):
        assert self._agenda_start
        assert self._agenda_end

        self._activity_start = current_time
        self._activity_end = self._activity_start + self._activity_delta


class Buffer_Fixed(BufferActivity):
    def __init__(self, act_desc: str, xcoord: int | float, ycoord: int | float, buffersize: int | float, duration: int, method=BufferCalculation.mean) -> None:
        super().__init__(act_desc)

        self.xcoord = xcoord
        self.ycoord = ycoord
        self.duration = duration
        self.buffersize = buffersize
        self.buffer_method = method

    def activity(self, current_time):
        assert self._agenda_start
        assert self._agenda_end

        self._activity_start = current_time
        self._activity_end = self._activity_start + self._activity_delta


class Buffer_Final(BufferActivity):
    def __init__(self, act_desc: str, xcoord: int | float, ycoord: int | float, buffersize: int | float, method=BufferCalculation.mean) -> None:
        super().__init__(act_desc)

        self.xcoord = xcoord
        self.ycoord = ycoord
        self.buffersize = buffersize
        self.buffer_method = method

    def activity(self, current_time):
        assert self._agenda_start
        assert self._agenda_end

        self._activity_start = current_time
        self._activity_end = self._agenda_end


class Commute(Activity):
    def __init__(self, act_desc: str, x1: int | float, y1: int | float, x2: int | float, y2: int | float, travel_mode, duration: int) -> None:
        """
        The commute activity.

        :param act_desc: activity description
        :param x1: x coordinate of start location
        :param y1: y coordinate of start location
        :param x2: x coordinate of destination location
        :param y2: y coordinate of destination location
        :param travel_mode: travel mode
        :param duration: duration in minutes
        """
        super().__init__()
        self._activity_type = ActivityType.route
        self._activity_description = act_desc

        self.start_x = x1
        self.start_y = y1
        self.dest_x = x2
        self.dest_y = y2

        self.travel_mode = travel_mode
        self.duration = duration

    def activity(self, current_time):
        assert self._agenda_start
        assert self._agenda_end
        assert self.duration > 0

        self._activity_start = current_time
        self._activity_end = self._activity_start + self.duration * self._time_delta
