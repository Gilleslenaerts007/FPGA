
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity efpga is
  Port ( 
            number1     : in std_logic_vector(31 downto 0);
            number2     : in std_logic_vector(31 downto 0);
            resultaat   : out std_logic_vector(31 downto 0)
  );
end efpga;

architecture Behavioral of efpga is

begin

resultaat <= std_logic_vector(unsigned(number1) mod unsigned(number2));


end Behavioral;