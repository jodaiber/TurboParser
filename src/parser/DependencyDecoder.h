/// Copyright (c) 2012-2013 Andre Martins
// All Rights Reserved.
//
// This file is part of TurboParser 2.1.
//
// TurboParser 2.1 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// TurboParser 2.1 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with TurboParser 2.1.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DEPENDENCYDECODER_H_
#define DEPENDENCYDECODER_H_

#include "Decoder.h"
#include "DependencyPart.h"
#include "ad3/FactorGraph.h"

class DependencyPipe;

class DependencyDecoder : public Decoder {
 public:
  DependencyDecoder() {};
  DependencyDecoder(DependencyPipe *pipe) : pipe_(pipe) {};
  virtual ~DependencyDecoder() {};

  void Decode(Instance *instance, Parts *parts, 
              const vector<double> &scores,
              vector<double> *predicted_output);

  void DecodePruner(Instance *instance, Parts *parts,
              const vector<double> &scores,
              vector<double> *predicted_output);

  void DecodePrunerNaive(Instance *instance, Parts *parts,
              const vector<double> &scores,
              vector<double> *predicted_output);

  void DecodeCostAugmented(Instance *instance, Parts *parts,
                           const vector<double> &scores,
                           const vector<double> &gold_output,
                           vector<double> *predicted_output,
                           double *cost,
                           double *loss);

  void DecodeMarginals(Instance *instance, Parts *parts,
                       const vector<double> &scores,
                       const vector<double> &gold_output,
                       vector<double> *predicted_output,
                       double *entropy,
                       double *loss);

  void RunChuLiuEdmonds(int sentence_length,
                        const vector<DependencyPartArc*> &arcs,
                        const vector<double> &scores,
                        vector<int> *heads,
                        double *value);

 protected:
  void DecodeLabels(Instance *instance, Parts *parts,
                    const vector<double> &scores,
                    vector<int> *best_labeled_parts);

  void DecodeLabelMarginals(Instance *instance, Parts *parts,
                            const vector<double> &scores,
                            vector<double> *total_scores,
                            vector<double> *label_marginals);

  void DecodeBasic(Instance *instance, Parts *parts, 
                   const vector<double> &scores,
                   vector<double> *predicted_output,
                   double *value);

  void DecodeMatrixTree(Instance *instance, Parts *parts,
                        const vector<double> &scores,
                        vector<double> *predicted_output,
                        double *log_partition_function,
                        double *entropy);

  void DecodeFactorGraph(Instance *instance, Parts *parts,
                         const vector<double> &scores,
                         bool single_root,
                         bool relax,
                         vector<double> *predicted_output);

  void RunChuLiuEdmondsIteration(vector<bool> *disabled,
                                 vector<vector<int> > *candidate_heads,
                                 vector<vector<double> > *candidate_scores,
                                 vector<int> *heads,
                                 double *value);

#ifdef USE_CPLEX
  void DecodeCPLEX(Instance *instance, Parts *parts,
                   const vector<double> &scores,
                   bool single_root,
                   bool relax,
                   vector<double> *predicted_output);
#endif
 protected:
  DependencyPipe *pipe_;
};

#endif /* DEPENDENCYDECODER_H_ */
