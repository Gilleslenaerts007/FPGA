  
----------------------------------------------------------------------------------
-- Company:     Hogeschool PXL
-- Engineer:    Vincent claes
-- 
-- Create Date: 27.11.2017 10:20:30
-- Design Name: 
-- Module Name: WS2812 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- by Vincent Claes
-- vincent.claes[at]pxl.be
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity WS2812 is
    generic(
        clock_frequency: integer := 50_000_000 -- Hertz
    );
    Port ( 
        clk:    in  std_logic;
        d_out:  out std_logic;
		LED_0: IN std_logic_vector(23 downto 0);
		LED_1: IN std_logic_vector(23 downto 0);
		LED_2: IN std_logic_vector(23 downto 0);
		LED_3: IN std_logic_vector(23 downto 0);
		LED_4: IN std_logic_vector(23 downto 0);
		LED_5: IN std_logic_vector(23 downto 0);
		LED_6: IN std_logic_vector(23 downto 0);
		LED_7: IN std_logic_vector(23 downto 0);
		LED_8: IN std_logic_vector(23 downto 0);
		LED_9: IN std_logic_vector(23 downto 0);
		LED_10: IN std_logic_vector(23 downto 0);
		LED_11: IN std_logic_vector(23 downto 0)
    );
end WS2812;

architecture Behavioral of WS2812 is

    constant T0_h   :   integer := 17;
    constant T0_l   :   integer := 38;
    constant T1_h   :   integer := 35;
    constant T1_l   :   integer := 28;
    constant Reset  :   integer := 2500;
    
    type LED_matrix is array(0 to 10)   of std_logic_vector(23 downto 0);
    type st_machine is (loading_state, sending_state, send_bit_state,reset_state);

begin
    process
        variable    state               : st_machine := loading_state;
        variable    GRB                 : std_logic_vector (23 downto 0)    := x"000000";
        variable    delay_high_cntr     : integer := 0;
        variable    delay_low_cntr      : integer := 0;
        variable    index               : integer := 0;
        variable    bit_cntr            : integer := 0;
		
																-- Green Red Blue
        variable    LEDS                : LED_matrix    := (
                                                                x"000000",  -- LED 0, Green Red Blue
                                                                x"000000",  -- LED 1
                                                                x"000000",  -- LED 2
                                                                x"000000",  -- LED 3
                                                                x"000000",  -- LED 4
                                                                x"000000",  -- LED 5
                                                                x"000000",  -- LED 6
                                                                x"000000",  -- LED 7
                                                                x"000000",  -- LED 8
                                                                x"000000",  -- LED 9
                                                                x"000000",  -- LED 10
                                                                x"000000"  -- LED 11                                   
                                                         );  -- LED 63
																
begin
    wait until rising_edge(clk);
    
    case state is
        when loading_state  =>
                                GRB         := LEDS(index);
                                bit_cntr    := 24;
                                state       := sending_state;
        when sending_state  =>
                                if( bit_cntr  > 0) then
                                    bit_cntr    := bit_cntr -1;
                                    if GRB(bit_cntr) ='1' then
                                        delay_high_cntr := T1_h;
                                        delay_low_cntr  := T1_l;
                                    else
                                        delay_high_cntr := T0_h;
                                        delay_low_cntr  := T0_l;
                                    end if;
                                    state   := send_bit_state;
                                else
                                    if( index < 63) then
                                        index   := index + 1;
                                        state   := loading_state;
                                    else
                                        delay_low_cntr := Reset;
                                        state          := reset_state;
                                    end if;
                                end if;
        when send_bit_state =>
                                if (delay_high_cntr > 0) then
                                    d_out <= '1';
                                    delay_high_cntr := delay_high_cntr - 1;
                                elsif (delay_low_cntr > 0) then
                                    d_out <= '0';
                                    delay_low_cntr := delay_low_cntr - 1;
                                else
                                    state := sending_state;
                                end if;
        when reset_state    =>
                                if (delay_low_cntr > 0) then
                                    d_out <= '0';
                                    delay_low_cntr := delay_low_cntr - 1;
                                else
                                    index := 0;
                                end if;
        when others         => 
                                NULL;
    end case;
 end process;
end Behavioral;

