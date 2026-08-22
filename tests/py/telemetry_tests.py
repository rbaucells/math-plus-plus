import mathpy

__all__ = ['start', 'end', 'asserts']

__startTelemetryStats__: mathpy.TelemetryStats
__endTelemetryStats__: mathpy.TelemetryStats

def start():
    global __startTelemetryStats__
    __startTelemetryStats__ = mathpy.Telemetry.snapshot()

def end():
    global __endTelemetryStats__
    __endTelemetryStats__ = mathpy.Telemetry.snapshot()

def asserts(expected: mathpy.TelemetryStats):
    assert __endTelemetryStats__.copy_constructs - __startTelemetryStats__.copy_constructs == expected.copy_constructs
    assert __endTelemetryStats__.move_constructs - __startTelemetryStats__.move_constructs == expected.move_constructs
    assert __endTelemetryStats__.copy_assigns - __startTelemetryStats__.copy_assigns == expected.copy_assigns
    assert __endTelemetryStats__.move_assigns - __startTelemetryStats__.move_assigns == expected.move_assigns
    assert __endTelemetryStats__.allocations - __startTelemetryStats__.allocations == expected.allocations
    assert __endTelemetryStats__.deallocations - __startTelemetryStats__.deallocations == expected.deallocations
    assert __endTelemetryStats__.dimensions_checks - __startTelemetryStats__.dimensions_checks == expected.dimensions_checks