#!/usr/bin/env bash

# we need bash 4 for associative arrays
if [ "${BASH_VERSION%%[^0-9]*}" -lt "4" ]; then
  echo "BASH VERSION < 4: ${BASH_VERSION}" >&2
  exit 1
fi

# associative array for the platforms that will be verified in build_main_platforms()
# this will be eval'd in the functions below because arrays can't be exported
export MAIN_PLATFORMS='declare -A main_platforms=( [uno]="arduino:avr:uno" [due]="arduino:sam:arduino_due_x" [zero]="arduino:samd:zero" [esp8266]="esp8266:esp8266:huzzah" [leonardo]="arduino:avr:leonardo" )'

# associative array for other platforms that can be called explicitly in .travis.yml configs
# this will be eval'd in the functions below because arrays can't be exported
export AUX_PLATFORMS='declare -A aux_platforms=( [trinket]="adafruit:avr:trinket5" [gemma]="arduino:avr:gemma" )'

# make display available for arduino CLI
/sbin/start-stop-daemon --start --quiet --pidfile /tmp/custom_xvfb_1.pid --make-pidfile --background --exec /usr/bin/Xvfb -- :1 -ac -screen 0 1280x1024x16
sleep 3
export DISPLAY=:1.0

# download and install arduino 1.6.5
wget https://downloads.arduino.cc/arduino-1.6.5-linux64.tar.xz
tar xf arduino-1.6.5-linux64.tar.xz
mv arduino-1.6.5 $HOME/arduino_ide

# move this library to the arduino libraries folder
ln -s $PWD $HOME/arduino_ide/libraries/Adafruit_Test_Library

# add the arduino CLI to our PATH
export PATH="$HOME/arduino_ide:$PATH"

echo -e "\n########################################################################";
echo "INSTALLING DEPENDENCIES"
echo "########################################################################";


# install the due, esp8266, and adafruit board packages
echo -n "ADD PACKAGE INDEX: "
DEPENDENCY_OUTPUT=$(arduino --pref "boardsmanager.additional.urls=https://adafruit.github.io/arduino-board-index/package_adafruit_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json" --save-prefs 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

echo -n "DUE: "
DEPENDENCY_OUTPUT=$(arduino --install-boards arduino:sam 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

echo -n "ZERO: "
DEPENDENCY_OUTPUT=$(arduino --install-boards arduino:samd 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

echo -n "ESP8266: "
DEPENDENCY_OUTPUT=$(arduino --install-boards esp8266:esp8266 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

echo -n "ADAFRUIT AVR: "
DEPENDENCY_OUTPUT=$(arduino --install-boards adafruit:avr 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

# install random lib so the arduino IDE grabs a new library index
# see: https://github.com/arduino/Arduino/issues/3535
echo -n "UPDATE LIBRARY INDEX: "
DEPENDENCY_OUTPUT=$(arduino --install-library USBHost > /dev/null 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

# set the maximal compiler warning level
echo -n "SET BUILD PREFERENCES: "
DEPENDENCY_OUTPUT=$(arduino --pref "compiler.warning_level=all" --save-prefs 2>&1)
if [ $? -ne 0 ]; then echo -e "\xe2\x9c\x96"; else echo -e "\xe2\x9c\x93"; fi

# init the json temp var for the current platform
export PLATFORM_JSON=""

# init test stats counters
export PASS_COUNT=0
export SKIP_COUNT=0
export FAIL_COUNT=0
export PDE_COUNT=0

# build all of the examples for the passed platform
function build_platform()
{

  # arrays can't be exported, so we have to eval
  eval $MAIN_PLATFORMS
  eval $AUX_PLATFORMS

  # reset platform json var
  PLATFORM_JSON=""

  # expects argument 1 to be the platform key
  local platform_key=$1

  # placeholder for platform
  local platform=""

  # track the exit code for this platform
  local exit_code=0

  # grab all pde and ino example sketches
  declare -a examples

  # loop through results and add them to the array
  examples=($(find $PWD -name "*.pde" -o -name "*.ino"))

  # get the last example in the array
  local last="${examples[@]:(-1)}"

  # grab the platform info from array or bail if invalid
  if [[ ${main_platforms[$platform_key]} ]]; then
    platform=${main_platforms[$platform_key]}
  elif [[ ${aux_platforms[$platform_key]} ]]; then
    platform=${aux_platforms[$platform_key]}
  else
    echo "NON-STANDARD PLATFORM KEY: $platform_key"
    platform=$platform_key
  fi

  echo -e "\n########################################################################";

  echo -n "SWITCHING TO ${platform_key}: "

  # switch to the requested board.
  # we have to avoid reading the exit code of local:
  # "when declaring a local variable in a function, the local acts as a command in its own right"
  local platform_stdout
  platform_stdout=$(arduino --board $platform --save-prefs 2>&1)

  # grab the exit status of the arduino board change
  local platform_switch=$?

  # notify if the platform switch failed
  if [ $platform_switch -ne 0 ]; then
    # heavy X
    echo -e "\xe2\x9c\x96"
    echo $platform_stdout
    exit_code=1
  else
    # heavy checkmark
    echo -e "\xe2\x9c\x93"
  fi

  echo "########################################################################";

  # loop through example sketches
  for example in "${examples[@]}"; do

    # store the full path to the example's sketch directory
    local example_dir=$(dirname $example)

    # store the filename for the example without the path
    local example_file=$(basename $example)

    # is this the last example in the loop
    local last_example=0
    if [ "$last" == "$example" ]; then
      last_example=1
    fi

    echo -n "$example_file: "

    # continue to next example if platform switch failed
    if [ $platform_switch -ne 0 ]; then
      # heavy X
      echo -e "\xe2\x9c\x96"

      # add json
      PLATFORM_JSON="${PLATFORM_JSON}$(json_sketch 0 $example_file $last_example)"

      # increment fails
      FAIL_COUNT=$((FAIL_COUNT + 1))

      # mark fail
      exit_code=1

      continue

    fi

    # ignore this example if there is an all platform skip
    if [[ -f "${example_dir}/.test.skip" ]]; then

      # right arrow
      echo -e "\xe2\x9e\x9e"

      # add json
      PLATFORM_JSON="${PLATFORM_JSON}$(json_sketch -1 $example_file $last_example)"

      # increment skips
      SKIP_COUNT=$((SKIP_COUNT + 1))

      continue

    fi

    # ignore this example if there is a skip file preset for this specific platform
    if [[ -f "${example_dir}/.${platform_key}.test.skip" ]]; then

      # right arrow
      echo -e "\xe2\x9e\x9e"

      # add json
      PLATFORM_JSON="${PLATFORM_JSON}$(json_sketch -1 $example_file $last_example)"

      # increment skips
      SKIP_COUNT=$((SKIP_COUNT + 1))

      continue
    fi

    # make sure that all examples are .ino files
    if [[ $example =~ \.pde$ ]]; then

      # heavy X
      echo -e "\xe2\x9c\x96"

      echo -e "-------------------------- DEBUG OUTPUT --------------------------\n"
      echo "PDE EXTENSION. PLEASE UPDATE TO INO"
      echo -e "\n------------------------------------------------------------------\n"

      # add json
      PLATFORM_JSON="${PLATFORM_JSON}$(json_sketch 0 $example_file $last_example)"

      # increment fails
      FAIL_COUNT=$((FAIL_COUNT + 1))

      # mark as fail
      exit_code=1

      continue

    fi

    # verify the example, and save stdout & stderr to a variable
    # we have to avoid reading the exit code of local:
    # "when declaring a local variable in a function, the local acts as a command in its own right"
    local build_stdout
    build_stdout=$(arduino --verify $example 2>&1)

    # echo output if the build failed
    if [ $? -ne 0 ]; then

      # heavy X
      echo -e "\xe2\x9c\x96"

      echo -e "----------------------------- DEBUG OUTPUT -----------------------------\n"
      echo "$build_stdout"
      echo -e "\n------------------------------------------------------------------------\n"

      # add json
      PLATFORM_JSON="${PLATFORM_JSON}$(json_sketch 0 $example_file $last_example)"

      # increment fails
      FAIL_COUNT=$((FAIL_COUNT + 1))

      # mark as fail
      exit_code=1

    else

      # heavy checkmark
      echo -e "\xe2\x9c\x93"

      # add json
      PLATFORM_JSON="${PLATFORM_JSON}$(json_sketch 1 "$example_file" $last_example)"

      # increment passes
      PASS_COUNT=$((PASS_COUNT + 1))

    fi

  done

  return $exit_code

}

build_platform uno
