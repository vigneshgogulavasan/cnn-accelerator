// ----------------------------------------------------------------------------
// SystemC Top Module
//
//    HLS version: 10.0a/269363 Production Release
//       HLS date: Wed Nov  9 17:38:00 PST 2016
//  Flow Packages: HDL_Tcl 8.0a, SCVerify 8.0a
//
//   Generated by: xph3sei702@cimeld95
// Generated date: Wed Jan 24 16:08:29 CET 2018
//
// ----------------------------------------------------------------------------
//---------------------------------------------------
// scverify_top_tcl.cpp
//---------------------------------------------------

#include <iostream>
#include "scverify_top_tcl.h"
#include <mc_simulator_extensions.h>
// 
// -------------------------------------
// scverify_top
// top module instantiating reference design,
// DUT and comparator
// -------------------------------------
// 
#include <mt19937ar.c>


// ============================================
// Function: setup_debug
// --------------------------------------------

void scverify_top::setup_debug()
{
   
      // At the breakpoint, modify the local variables
      // above to turn on/off different levels of transaction
      // logging for each variable. Available flags are:
      //   MC_TRANSACTOR_EMPTY       - log empty FIFOs (on by default)
      //   MC_TRANSACTOR_UNDERFLOW   - log FIFOs that run empty and then are loaded again (off)
      //   MC_TRANSACTOR_READ        - log all read events
      //   MC_TRANSACTOR_WRITE       - log all write events
      //   MC_TRANSACTOR_LOAD        - log all FIFO load events
      //   MC_TRANSACTOR_DUMP        - log all FIFO dump events
      //   MC_TRANSACTOR_STREAMCNT   - log all streamed port index counter events
      //   MC_TRANSACTOR_WAIT        - log user specified handshake waits
      //   MC_TRANSACTOR_SIZE        - log input FIFO size updates
   
      std::ifstream debug_cmds;
      debug_cmds.open("scverify.cmd",std::fstream::in);
      if (debug_cmds.is_open()) {
         std::cout << "Reading SCVerify debug commands from file 'scverify.cmd'" << std::endl;
         std::string line;
         while (getline(debug_cmds,line)) {
            std::size_t pos1 = line.find(" ");
            if (pos1 == std::string::npos) continue;
            std::size_t pos2 = line.find(" ", pos1+1);
            std::string varname = line.substr(0,pos1);
            std::string flags = line.substr(pos1+1,pos2-pos1-1);
            std::string count = line.substr(pos2+1);
            debug(varname.c_str(),std::atoi(flags.c_str()),std::atoi(count.c_str()));
         }
         debug_cmds.close();
      } else {
      }
}
// ============================================
// Function: install_observe_foreign_signals
// --------------------------------------------

void scverify_top::install_observe_foreign_signals()
{
   #if !defined(CCS_DUT_SYSC) && defined(DEADLOCK_DETECTION)
   #if defined(CCS_DUT_CYCLE) || defined(CCS_DUT_RTL)
   #endif
   #endif
   #if !defined(CCS_DUT_SYSC)
   #if defined(CCS_DUT_CYCLE) || defined(CCS_DUT_RTL)
   #endif
   #endif
}
// ============================================
// Function: debug
// --------------------------------------------

void scverify_top::debug(const char *varname, int flags, int count)
{
   sc_module *xlator_p = 0;
   sc_attr_base *debug_attr_p = 0;
   if (strcmp(varname,"conv_in:b5a7c208-7b9a-4d45-86da-9349cbc64401-57:conv_in") == 0) {
      xlator_p = conv_in_transactor;
   }
   if (strcmp(varname,"conv_out:b5a7c208-7b9a-4d45-86da-9349cbc64401-58:conv_out") == 0) {
      xlator_p = conv_out_transactor;
   }
   if (xlator_p) {
      debug_attr_p = xlator_p->get_attribute("MC_TRANSACTOR_EVENT");
      if (!debug_attr_p) {
         debug_attr_p = new sc_attribute<int>("MC_TRANSACTOR_EVENT",flags);
         xlator_p->add_attribute(*debug_attr_p);
      }
      ((sc_attribute<int>*)debug_attr_p)->value = flags;
   }
   if (count>=0) {
      debug_attr_p = xlator_p->get_attribute("MC_TRANSACTOR_COUNT");
      if (!debug_attr_p) {
         debug_attr_p = new sc_attribute<int>("MC_TRANSACTOR_COUNT",count);
         xlator_p->add_attribute(*debug_attr_p);
      }
      ((sc_attribute<int>*)debug_attr_p)->value = count;
   }
}
// ---------------------------------------------------------------
// Process: SC_METHOD deadlock_notify
// Static sensitivity: sensitive << deadlock_event;

void scverify_top::deadlock_notify() {
   if (deadlocked.read() == SC_LOGIC_1) {
      testbench_INST->check_results();
      SC_REPORT_ERROR("System","Simulation deadlock detected");
      sc_stop();
   }
}
// ---------------------------------------------------------------
// Process: SC_METHOD deadlock_watch
// Static sensitivity: sensitive  << clk;

void scverify_top::deadlock_watch() {
   // DEADLOCK_WATCH
   #if !defined(CCS_DUT_SYSC) && defined(DEADLOCK_DETECTION)
   #if defined(CCS_DUT_CYCLE) || defined(CCS_DUT_RTL)
   #if defined(MTI_SYSTEMC) || defined(NCSC) || defined(VCS_SYSTEMC)
   #endif
   #endif
   #endif
   // DEADLOCK_WATCH END
}
// ---------------------------------------------------------------
// Process: SC_METHOD generate_sync
// Static sensitivity: sensitive << clk << rst;

void scverify_top::generate_sync() {
   static int active_edge = 1;
   static CATMON_EX_TYPE latency = 2023502LL; // Total Cycles value
   static CATMON_EX_TYPE init_interval = 0LL;
   static CATMON_EX_TYPE csteps = 2023502LL;
   static CATMON_EX_TYPE duration = latency - csteps + init_interval;
   static CATMON_EX_TYPE latest_write = 2023502LL;
   static bool top_loop_pipelined = 0;
   
   static CATMON_EX_TYPE max_state = init_interval ? duration : latency;
   
   static CATMON_EX_TYPE initial_in_state = ((init_interval>0)&&top_loop_pipelined&&(latency!=csteps)) ? 0 : 1;
   static CATMON_EX_TYPE initial_out_state = init_interval ? init_interval-latest_write+1 : 1;
   
   static int done_flag_used = 0;
   
   
   static CATMON_EX_TYPE in_state = initial_in_state;
   static CATMON_EX_TYPE out_state = initial_out_state;
   static sc_logic last_done = SC_LOGIC_0; // if DONE_FLAG used
   
   if (rst.read() == 1) {
      in_sync.write(SC_LOGIC_0);
      out_sync.write(SC_LOGIC_0);
      inout_sync.write(SC_LOGIC_0);
      catapult_start.write(SC_LOGIC_1);
      in_state = initial_in_state;
      last_done = SC_LOGIC_1;
      if (init_interval) {
         out_state = initial_out_state;
      } else {
         if (done_flag_used && (catapult_done.read() == 0)) wait_for_init = 0;
         out_state = initial_out_state;
      }
   } else {
     if (done_flag_used) {
         catapult_start.write(catapult_done.read()); // start follows done timing
         if (catapult_done.read() == SC_LOGIC_0) {
            // falling edge of done, deassert start
            wait_for_init.write(wait_for_init.read()+1);
            out_sync.write(SC_LOGIC_0);
            in_sync.write(SC_LOGIC_0);
            inout_sync.write(SC_LOGIC_0);
         } else {
            // rising edge of done, assert sync signals
            if (wait_for_init.read() > 1) {
               out_sync.write(SC_LOGIC_1);
               in_sync.write(SC_LOGIC_1);
               inout_sync.write(SC_LOGIC_1);
            }
         }
     } else {
      if ( clk.read() == active_edge ) {
         // wait for static array initialization loop to complete
         if (wait_for_init) {
            if (done_flag_used && (catapult_done.read() == 1)) wait_for_init = false;
         } else {
            if (((out_state >= max_state) && (init_interval || !done_flag_used)) || (done_flag_used && ((catapult_done.read() == 1) && (last_done == SC_LOGIC_0)))) {
               out_sync.write(SC_LOGIC_1);
               inout_sync.write(SC_LOGIC_1);
               out_state = 0;
               if (!init_interval) last_done = SC_LOGIC_1;
               if (init_interval == 0) in_state = max_state; // force in_sync to align with out_sync
            } else {
               if ( (init_interval == 0) && (catapult_done.read() == 0) && (last_done == SC_LOGIC_1) ) last_done = SC_LOGIC_0;
               out_sync.write(SC_LOGIC_0);
               inout_sync.write(SC_LOGIC_0);
            }
            out_state++;
         } // if (wait_for_init)
      } // if (clk.read() == active_edge)
   
      if ( clk.read() == active_edge ) {
         // wait for static array initialization loop to complete
         if (wait_for_init) {
            if (done_flag_used && (catapult_done.read() == 1)) wait_for_init = false;
         } else {
            if ( in_state >= max_state ) {
               in_sync.write(SC_LOGIC_1);
               inout_sync.write(SC_LOGIC_1);
               catapult_start.write(SC_LOGIC_1);
               in_state = 0;
            } else {
               if ( in_state == 1 ) {
                  catapult_start.write(SC_LOGIC_1);
               }
               in_sync.write(SC_LOGIC_0);
               inout_sync.write(SC_LOGIC_0);
               catapult_start.write(SC_LOGIC_1);
            }
            in_state++;
         }
      }
     } // if (done_flag_used)
   }
}
// ---------------------------------------------------------------
// Process: SC_METHOD generate_reset
// Static sensitivity: sensitive << reset_deactivation_event;

void scverify_top::generate_reset() {
      static bool first = true;
      if (first || sc_time_stamp() == SC_ZERO_TIME)
      {
         setup_debug();
         first = false;
         rst.write(SC_LOGIC_1);
         reset_deactivation_event.notify(120.0, SC_NS);
      } else {
         conv_in_transactor->reset_streams();
         conv_out_transactor->reset_streams();
         rst.write(SC_LOGIC_0);
      }
   
}
#if defined(MC_SIMULATOR_OSCI) || defined(MC_SIMULATOR_VCS)
int sc_main(int argc, char *argv[])
{
   sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
   scverify_top scverify_top("scverify_top");
   sc_start();
   return scverify_top.testbench_INST->failed();
}
#else
MC_MODULE_EXPORT(scverify_top);
#endif
