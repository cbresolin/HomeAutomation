import json
import serial
import argparse
import sys
import io

# Manage argument parser
parser = argparse.ArgumentParser(description='Control Arduino Uno actions')
parser.add_argument('-command', required=True, type=str, help='ReST command to be sent to Arduino (e.g. /id/, /blue/)')
parser.add_argument('-device', type=str, default='/dev/rfcomm0', help='Device to which the command is sent'
                                                                      '(e.g. /dev/rfcomm0; COM3)')
args = parser.parse_args()

try:
    serialPort = serial.Serial(port=args.device, timeout=5)
    sio = io.TextIOWrapper(io.BufferedRWPair(serialPort, serialPort))
    sio.write(unicode(args.command))
    sio.flush()
    UniResp = sio.readline()
    serialPort.close()

    dictResp = json.loads(UniResp)

    # Return values according to content
    if "message" in dictResp:
        print dictResp.get('message', 'None')
    elif "return_value" in dictResp:
        print dictResp.get('return_value', -1)
    else:
        print dictResp

except IOError as e:
    print "I/O error ({0}):{1}".format(e.errno, e.strerror)
except KeyError as e:
    print "Key Error on {0}".format(e)
except ValueError as e:
    print "Value error ({0})".format(e)
except:
    print "Unexpected error:", sys.exc_info()[0]
    raise

exit()
