#ifndef IMAGE_PROCESSING_SIMULATION_H
#define IMAGE_PROCESSING_SIMULATION_H

#include "../software/image_processing.hpp"
#include "../obj_dir/Vimage_processing.h"

struct Operation{
   bool is_command;
   Commands command;
   uint8_t data;

   Operation(bool is_command, Commands com, uint8_t data){
      this->is_command = is_command;
      this->command = com;
      this->data = data;
   }
};

typedef std::queue<Operation> FIFO_OP;

class Image_processing_simulation : public Image_processing{
public:
   Image_processing_simulation();
   ~Image_processing_simulation();

   virtual void send_params(uint16_t img_width, uint16_t img_height);
   virtual void read_status(uint8_t *output); //TODO vector?
   virtual void send_image(uint8_t *img);

   virtual void send_add(int16_t value, bool clamp);
   virtual void send_threshold(uint8_t threshold_value, uint8_t replacement, bool upper_selection);
   virtual void send_image_invert();
   virtual void send_mult(float value, bool clamp);

   virtual void wait_end_busy();

   virtual void read_image(uint8_t *img);

   virtual void switch_buffers();

   virtual void send_binary_add(bool clamp);
   virtual void send_binary_sub(bool clamp, bool absolute_diff);
   virtual void send_binary_mult(bool clamp);
   virtual void send_convolution(uint8_t *kernel, bool clamp, bool input_source, bool add_to_output);
   virtual void send_clear(uint8_t value);

private:
   void main_loop_clk();

   Vimage_processing *simulator;
   FIFO_OP fifo_in;
   std::queue<uint16_t> fifo_out;

   uint16_t *memory;
};

#endif
