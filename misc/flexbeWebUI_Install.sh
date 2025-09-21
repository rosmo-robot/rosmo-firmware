#!/usr/bin/env bash
set -e

# Ensure we are in workspace/src
if [ "$(basename "$(pwd)")" != "src" ]; then
  echo "Please run this script from inside your ROS 2 workspace 'src' folder."
  exit 1
fi

WORKSPACE_ROOT="$(pwd)/.."
SRC_DIR="${WORKSPACE_ROOT}/src"

echo "Installing FlexBE WebUI into ROS 2 workspace at: $WORKSPACE_ROOT"

# Clone flexbe_behavior_engine
if [ ! -d "${SRC_DIR}/flexbe_behavior_engine" ]; then
  echo "Cloning flexbe_behavior_engine..."
  git clone -b ros2-devel https://github.com/FlexBE/flexbe_behavior_engine.git "${SRC_DIR}/flexbe_behavior_engine"
else
  echo "Updating flexbe_behavior_engine..."
  (cd "${SRC_DIR}/flexbe_behavior_engine" && git pull)
fi

# Clone flexbe_webui
if [ ! -d "${SRC_DIR}/flexbe_webui" ]; then
  echo "Cloning flexbe_webui..."
  git clone https://github.com/FlexBE/flexbe_webui.git "${SRC_DIR}/flexbe_webui"
else
  echo "Updating flexbe_webui..."
  (cd "${SRC_DIR}/flexbe_webui" && git pull)
fi

# System dependencies
echo "Running rosdep..."
cd "${WORKSPACE_ROOT}"
rosdep update
rosdep install --from-paths src --ignore-src -r -y

# Create virtualenv for PySide6 (needed on Ubuntu 24.04)
if [ ! -d "${WORKSPACE_ROOT}/venv" ]; then
  echo "Creating Python virtualenv for PySide6..."
  python3 -m venv --system-site-packages "${WORKSPACE_ROOT}/venv"
  # Ignore venv during colcon builds
  touch "${WORKSPACE_ROOT}/venv/COLCON_IGNORE"
fi

# Activate venv and install Python deps
echo "Installing Python dependencies into virtualenv..."
source "${WORKSPACE_ROOT}/venv/bin/activate"
pip install -r "${SRC_DIR}/flexbe_webui/requires.txt"
deactivate

# Build with colcon
echo "Building workspace with colcon..."
colcon build --symlink-install

# Add venv site-packages to PYTHONPATH for runtime
SITE_PACKAGES="$(find "${WORKSPACE_ROOT}/venv/lib" -type d -name site-packages | head -n1)"
if ! grep -q "$SITE_PACKAGES" <<< "$PYTHONPATH"; then
  echo "Adding venv site-packages to PYTHONPATH..."
  echo "export PYTHONPATH=\$PYTHONPATH:$SITE_PACKAGES" >> "${WORKSPACE_ROOT}/.flexbe_env"
  echo "Source this file in your terminal before running FlexBE:"
  echo "  source ${WORKSPACE_ROOT}/.flexbe_env"
fi

echo
echo "FlexBE WebUI installation complete."
echo
echo "To run the Operator Control Station (OCS):"
echo "  ros2 launch flexbe_webui flexbe_ocs.launch.py"
echo
echo "For headless mode + separate client:"
echo "  ros2 launch flexbe_webui flexbe_ocs.launch.py headless:=true"
echo "  ros2 run flexbe_webui webui_client"
echo
