# Sparoku Status

This is a firmware for Spark Core with [Button](https://www.spark.io/button) to make the device ready to work with [Sparoku Drains](https://github.com/heroku/sparoku-drain).

It relies on [SparkButton](https://github.com/jenesaisdiq/SparkButton) to control the lights on the button shield.


## Setup

```bash
# install dfu-util so you can update your Spark Core via USB:
$ brew install dfu-util

# so we can help you update the firmware on the device:
$ export SPARK_DEVICE=$YOUR_SPARK_DEVICE_NAME

# to actually update it:
$ rake
```

## Testing locally

Before hooking this up to a drain you can test it locally like:

```
DYNO=1 COLOR=green rake simulate
```