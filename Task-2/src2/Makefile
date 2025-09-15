MODULES = statement_tracker
EXTENSION = statement_tracker
DATA = statement_tracker--1.0.sql

PG_CONFIG = /home/praveen-pt7975/Documents/allBuilds/REL_17_0_build/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)

override CC = g++
CXXFLAGS = -std=c++17 -fPIC -Wall

include $(PGXS)