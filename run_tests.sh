EXEC=$1
TMP_OUT=$2

echo "Executando testes:"
for i in {1..10..1}; do
  testname=$(printf "%d" $i)
  $EXEC < ../CasosTeste/input0$i.txt > $TMP_OUT
  if ! diff -qwB ../CasosTeste/out0$i.txt $TMP_OUT &>/dev/null; then
    echo "Test $testname failed"
  else
    echo "Test $testname passed"
  fi
done

rm $TMP_OUT