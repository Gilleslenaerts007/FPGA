----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 16.10.2018 16:39:48
-- Design Name: 
-- Module Name: RekenMachine - Behavioral
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
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity RekenMachine is
    Port ( Getal_1 : in STD_LOGIC_VECTOR (31 downto 0);
           Getal_2 : in STD_LOGIC_VECTOR (31 downto 0);
           Bewerking : in STD_LOGIC_VECTOR (2 downto 0);
           Resultaat : out STD_LOGIC_VECTOR (31 downto 0));
end RekenMachine;

architecture Behavioral of RekenMachine is

begin

process(Getal_1, Getal_2, Bewerking)
begin
    
    case Bewerking is
        when "000" => 
            Resultaat <= std_logic_vector(Signed(Getal_1) + Signed(Getal_2));
        when "001" => 
            Resultaat <= std_logic_vector(Signed(Getal_1) - Signed(Getal_2));
        when "010" => 
            Resultaat <= std_logic_vector(Signed(Getal_2) - Signed(Getal_1));
        when "011" => 
            Resultaat <= std_logic_vector(Signed(Getal_1(15 downto 0)) * Signed(Getal_2(15 downto 0)));
        when "100" => 
            Resultaat <= std_logic_vector(Signed(Getal_1) / Signed(Getal_2));
        when "101" => 
            Resultaat <= std_logic_vector(Signed(Getal_2) / Signed(Getal_1));
        when "110" => 
            Resultaat <= std_logic_vector(Signed(Getal_1) mod Signed(Getal_2));
        when "111" => 
            Resultaat <= std_logic_vector(Signed(Getal_2) mod Signed(Getal_1));
        when others => null;
    end case;
    
end process;

end Behavioral;
